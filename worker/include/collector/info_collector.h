#pragma once
#ifndef MONITOR_INFO_COLECTOR_H
#define MONITOR_INFO_COLECTOR_H

#include <memory>
#include <vector>

#include "collector/collector_interface.h"

namespace monitor {

class InfoCollector {
public:
    InfoCollector();
    ~InfoCollector();

    InfoCollector(InfoCollector &&other) = default;
    InfoCollector &operator=(InfoCollector &&other) = default;

    MonitorInfo collectInfo();

private:
    std::vector<std::unique_ptr<CollectorInterface>> m_collectors;

    InfoCollector(const InfoCollector &) = delete;
    InfoCollector &operator=(const InfoCollector &) = delete;
};

} // namespace monitor

#endif