#pragma once
#ifndef MONITOR_SIGNAL_HANDLER_H
#define MONITOR_SIGNAL_HANDLER_H

namespace monitor {

class SignalHandler {
public:
    ~SignalHandler();

    static SignalHandler &getInstance();
    void waitForShutdownSignal();

private:
    SignalHandler();

    static void handleSignal(int signal);
    static int *getSignalPipe();

    void setupSignalHandler();
    void cleanUp();

    SignalHandler(const SignalHandler &) = delete;
    SignalHandler(SignalHandler &&) = delete;
    SignalHandler &operator=(const SignalHandler &) = delete;
    SignalHandler &operator=(SignalHandler &&) = delete;
};

} // namespace monitor

#endif