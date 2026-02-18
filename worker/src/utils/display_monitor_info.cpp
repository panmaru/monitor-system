#include "utils/display_monitor_info.h"
#include "utils/info.h"

#include <print>

namespace monitor {

void displayMonitorInfo(const MonitorInfo &monitorInfo) {
    std::println("\n{}=========================== Monitor Info "
                 "==========================={}",
                 ansi::yellow, ansi::reset);

    if (monitorInfo.has_hostinfo()) {
        displayHostInfo(monitorInfo.hostinfo());
    }

    std::println("{}=========================================="
                 "==========================={}\n",
                 ansi::yellow, ansi::reset);
}

void displayHostInfo(const HostInfo &hostInfo) {
    std::println("{}[HOST]{} {}Hostname{}: {}, {}IP Address{}: {}", ansi::green,
                 ansi::reset, ansi::blue, ansi::reset, hostInfo.hostname(),
                 ansi::blue, ansi::reset, hostInfo.ipaddress());
}

} // namespace monitor