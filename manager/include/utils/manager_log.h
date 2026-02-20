#pragma once
#ifndef MONITOR_MANAGER_LOG_H
#define MONITOR_MANAGER_LOG_H

#include "utils/log.h"

namespace monitor {

template <typename... Args>
void managerLog(std::format_string<Args...> fmt, Args &&...args) {
    log("manager", fmt, std::forward<Args>(args)...);
}

} // namespace monitor

#endif