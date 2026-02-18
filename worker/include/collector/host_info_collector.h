#pragma once
#ifndef MONITOR_HOST_INFO_COLLECTOR_H
#define MONITOR_HOST_INFO_COLLECTOR_H

#include "collector/collector_interface.h"

namespace monitor {

class HostInfoCollector : public monitor::CollectorInterface {
public:
    HostInfoCollector() = default;
    ~HostInfoCollector() override = default;

    HostInfoCollector(HostInfoCollector &&other) = default;
    HostInfoCollector &operator=(HostInfoCollector &&other) = default;

    void collectInfo(MonitorInfo &monitorInfo) override;
    void stop() override;

private:
    std::string getHostname();
    std::string getIpAddress();

    HostInfoCollector(const HostInfoCollector &) = delete;
    HostInfoCollector &operator=(const HostInfoCollector &) = delete;
};

} // namespace monitor

#endif