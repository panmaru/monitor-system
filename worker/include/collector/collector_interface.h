#pragma once
#ifndef MONITOR_COLLECTOR_INTERFACE_H
#define MONITOR_COLLECTOR_INTERFACE_H

#include "monitor_info.pb.h"

namespace monitor {

class CollectorInterface {
public:
    CollectorInterface() = default;
    virtual ~CollectorInterface();

    CollectorInterface(CollectorInterface &&other) = default;
    CollectorInterface &operator=(CollectorInterface &&other) = default;

    virtual void collectInfo(MonitorInfo &monitorInfo) = 0;
    virtual void stop();

private:
    CollectorInterface(const CollectorInterface &) = delete;
    CollectorInterface &operator=(const CollectorInterface &) = delete;
};

} // namespace monitor

#endif