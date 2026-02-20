#include <absl/flags/flag.h>
#include <absl/flags/parse.h>
#include <absl/flags/usage.h>

#include "rpc/monitor_info_reporter.h"
#include "utils/signal_handler.h"
#include "utils/worker_config.h"
#include "utils/worker_log.h"

ABSL_FLAG(std::string, manager_address, "localhost:50051",
          "The address of the manager server");
ABSL_FLAG(int, interval_seconds, 10,
          "The interval in seconds for pushing monitor data");

monitor::WorkerConfig parseCommandLine(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    monitor::WorkerConfig config = parseCommandLine(argc, argv);

    monitor::workerLog("Starting monitor worker...");
    monitor::MonitorInfoReporter reporter(config);
    reporter.start();

    monitor::workerLog("Press Ctrl+C to stop");
    monitor::SignalHandler &signalHandler =
        monitor::SignalHandler::getInstance();
    signalHandler.waitForShutdownSignal();

    monitor::workerLog("Stopping monitor worker gracefully...");
    // reporter will stop automatically,
    // no need to call reporter.stop() manually
}

monitor::WorkerConfig parseCommandLine(int argc, char *argv[]) {
    std::string usageMessage =
        std::format("Worker node for monitoring system.\n"
                    "Usage: {}"
                    " [--manager_address=<address>]"
                    " [--interval_seconds=<seconds>]",
                    argv[0]);
    absl::SetProgramUsageMessage(usageMessage);

    absl::ParseCommandLine(argc, argv);
    std::string managerAddress = absl::GetFlag(FLAGS_manager_address);
    int intervalSeconds = absl::GetFlag(FLAGS_interval_seconds);

    return monitor::WorkerConfig{.managerAddress = managerAddress,
                                 .intervalSeconds = intervalSeconds};
}
