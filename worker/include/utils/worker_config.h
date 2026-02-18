#pragma once
#ifndef MONITOR_WORKER_CONFIG_H
#define MONITOR_WORKER_CONFIG_H

#include <string>

namespace monitor {

struct WorkerConfig {
    std::string managerAddress;
    int intervalSeconds;
};

} // namespace monitor

#endif