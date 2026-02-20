#pragma once
#ifndef MONITOR_MANAGER_CONFIG_H
#define MONITOR_MANAGER_CONFIG_H

#include <string>

namespace monitor {

struct ManagerConfig {
    std::string listenAddress;
    int hostExpireSeconds;
};

} // namespace monitor

#endif