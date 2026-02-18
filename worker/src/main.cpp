#include <csignal>
#include <poll.h>
#include <unistd.h>

#include <absl/flags/flag.h>
#include <absl/flags/parse.h>
#include <absl/flags/usage.h>

#include "rpc/monitor_pusher.h"
#include "utils/info.h"
#include "utils/worker_config.h"

ABSL_FLAG(std::string, manager_address, "localhost:50051",
          "The address of the manager server");
ABSL_FLAG(int, interval_seconds, 10,
          "The interval in seconds for pushing monitor data");

int *getSignalPipe() {
    static int signalPipe[2];
    return signalPipe;
}

monitor::WorkerConfig parseCommandLine(int argc, char *argv[]);
void setupSignalHandler();
void waitForShutdownSignal();
void cleanUp();

int main(int argc, char *argv[]) {
    monitor::WorkerConfig config = parseCommandLine(argc, argv);

    monitor::info("Starting monitor worker...");
    monitor::MonitorPusher pusher(config);
    pusher.start();

    monitor::info("Press Ctrl+C to stop");

    setupSignalHandler();
    waitForShutdownSignal();

    monitor::info("Stopping monitor worker gracefully ...");
    pusher.stop();
    cleanUp();
}

void handleSignal(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        char msg = 'x';
        int *signalPipe = getSignalPipe();
        write(signalPipe[1], &msg, 1);
    }
}

void setupSignalHandler() {
    int *signalPipe = getSignalPipe();
    pipe(signalPipe);

    struct sigaction sa{};
    sa.sa_handler = handleSignal;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaddset(&sa.sa_mask, SIGTERM);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, nullptr);
    sigaction(SIGTERM, &sa, nullptr);
}

void waitForShutdownSignal() {
    int *signalPipe = getSignalPipe();

    pollfd pfd[1];
    pfd[0].fd = signalPipe[0];
    pfd[0].events = POLLIN;
    while (true) {
        int ret = poll(pfd, 1, -1);
        if (ret > 0 && pfd[0].revents & POLLIN) {
            char msg;
            read(signalPipe[0], &msg, 1);
            break;
        }
    }
}

monitor::WorkerConfig parseCommandLine(int argc, char *argv[]) {
    std::string usageMessage =
        std::format("Worker node for monitoring system.\nUsage: {}"
                    " [--manager_address=<manager_address>]"
                    " [--interval_seconds=<interval_seconds>]",
                    argv[0]);
    absl::SetProgramUsageMessage(usageMessage);

    absl::ParseCommandLine(argc, argv);
    std::string managerAddress = absl::GetFlag(FLAGS_manager_address);
    int intervalSeconds = absl::GetFlag(FLAGS_interval_seconds);

    return monitor::WorkerConfig{.managerAddress = managerAddress,
                                 .intervalSeconds = intervalSeconds};
}

void cleanUp() {
    int *signalPipe = getSignalPipe();
    close(signalPipe[0]);
    close(signalPipe[1]);
}