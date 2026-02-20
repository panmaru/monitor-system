#include "utils/signal_handler.h"

#include <csignal>
#include <poll.h>
#include <unistd.h>

namespace monitor {

SignalHandler::SignalHandler() { setupSignalHandler(); }

SignalHandler::~SignalHandler() { cleanUp(); }

SignalHandler &SignalHandler::getInstance() {
    static SignalHandler instance;
    return instance;
}

void SignalHandler::waitForShutdownSignal() {
    pollfd pfd[1];
    pfd[0].fd = getSignalPipe()[0];
    pfd[0].events = POLLIN;
    while (true) {
        int ret = poll(pfd, 1, -1);
        if (ret > 0 && pfd[0].revents & POLLIN) {
            char msg;
            read(getSignalPipe()[0], &msg, 1);
            break;
        }
    }
}

void SignalHandler::setupSignalHandler() {
    pipe(getSignalPipe());

    struct sigaction sa{};
    sa.sa_handler = handleSignal;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaddset(&sa.sa_mask, SIGTERM);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, nullptr);
    sigaction(SIGTERM, &sa, nullptr);
}

void SignalHandler::cleanUp() {
    close(getSignalPipe()[0]);
    close(getSignalPipe()[1]);
}

void SignalHandler::handleSignal(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        char msg = 'x';
        write(getSignalPipe()[1], &msg, 1);
    }
}

int *SignalHandler::getSignalPipe() {
    static int signalPipe[2];
    return signalPipe;
}

} // namespace monitor