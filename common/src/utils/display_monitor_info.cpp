#include "utils/display_monitor_info.h"

#include <google/protobuf/util/time_util.h>
#include <print>

#include "utils/log.h"

namespace monitor {

void displayMonitorInfo(const MonitorInfo &monitorInfo) {
    std::println("\n{}=========================== Monitor Info "
                 "==========================={}",
                 ansi::yellow, ansi::reset);

    if (monitorInfo.has_collecttime()) {
        displayCollectTime(monitorInfo.collecttime());
    }

    if (monitorInfo.has_hostinfo()) {
        displayHostInfo(monitorInfo.hostinfo());
    }

    std::println("{}=========================================="
                 "==========================={}\n",
                 ansi::yellow, ansi::reset);
}

void displayCollectTime(const google::protobuf::Timestamp &timestamp) {
    auto seconds = timestamp.seconds();
    std::chrono::sys_seconds sysTime((std::chrono::seconds(seconds)));
    auto ztime = std::chrono::zoned_time(std::chrono::current_zone(), sysTime);

    std::println("{}[TIME]{} {}Collect Time{}: {:%Y-%m-%d %H:%M:%S %z (%Z)}",
                 ansi::green, ansi::reset, ansi::blue, ansi::reset, ztime);
}

void displayHostInfo(const HostInfo &hostInfo) {
    std::println("{}[HOST]{} {}Hostname{}: {}, {}IP Address{}: {}", ansi::green,
                 ansi::reset, ansi::blue, ansi::reset, hostInfo.hostname(),
                 ansi::blue, ansi::reset, hostInfo.ipaddress());
}

} // namespace monitor