#pragma once
#ifndef MONITOR_MONITOR_INFO_COLECTOR_H
#define MONITOR_MONITOR_INFO_COLECTOR_H

#include <memory>
#include <vector>

#include "collector/collector_interface.h"

namespace monitor {

class MonitorInfoCollector {
public:
    MonitorInfoCollector();
    ~MonitorInfoCollector();

    MonitorInfoCollector(MonitorInfoCollector &&other) = default;
    MonitorInfoCollector &operator=(MonitorInfoCollector &&other) = default;

    MonitorInfo collectInfo();

private:
    std::vector<std::unique_ptr<CollectorInterface>> m_collectors;

    MonitorInfoCollector(const MonitorInfoCollector &) = delete;
    MonitorInfoCollector &operator=(const MonitorInfoCollector &) = delete;
};

} // namespace monitor

#endif