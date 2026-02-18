#pragma once
#ifndef MONITOR_DISPLAY_MONITOR_INFO_H
#define MONITOR_DISPLAY_MONITOR_INFO_H

#include "monitor_info.pb.h"

namespace monitor {

void displayMonitorInfo(const MonitorInfo &monitorInfo);

void displayHostInfo(const HostInfo &hostInfo);

} // namespace monitor

#endif