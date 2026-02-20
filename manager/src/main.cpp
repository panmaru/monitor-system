#include <absl/flags/flag.h>
#include <absl/flags/parse.h>
#include <absl/flags/usage.h>

#include "server/manager_server.h"
#include "utils/manager_config.h"
#include "utils/manager_log.h"
#include "utils/signal_handler.h"

ABSL_FLAG(std::string, listen_address, "0.0.0.0:50051",
          "The address to listen on");
ABSL_FLAG(int, host_expire_seconds, 60, "The host expire time");

monitor::ManagerConfig parseCommandLine(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    monitor::ManagerConfig config = parseCommandLine(argc, argv);

    monitor::managerLog("Starting monitor manager...");
    monitor::ManagerServer server(config);
    server.start();

    monitor::managerLog("Press Ctrl+C to stop");
    monitor::SignalHandler &signalHandler =
        monitor::SignalHandler::getInstance();
    signalHandler.waitForShutdownSignal();

    monitor::managerLog("Stopping monitor manager gracefully...");
    // server will stop automatically,
    // no need to call server.stop() manually
}

monitor::ManagerConfig parseCommandLine(int argc, char *argv[]) {
    std::string usageMessage = std::format("Manager for monitoring system.\n"
                                           "Usage: {}"
                                           " [--listen_address=<address>]"
                                           " [--host_expire_seconds=<seconds>]",
                                           argv[0]);
    absl::SetProgramUsageMessage(usageMessage);

    absl::ParseCommandLine(argc, argv);
    std::string listenAddress = absl::GetFlag(FLAGS_listen_address);
    int hostExpireSeconds = absl::GetFlag(FLAGS_host_expire_seconds);

    return monitor::ManagerConfig{.listenAddress = listenAddress,
                                  .hostExpireSeconds = hostExpireSeconds};
}