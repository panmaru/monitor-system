#pragma once
#ifndef MONITOR_WORKER_INFO_H
#define MONITOR_WORKER_INFO_H

#include "utils/log.h"

namespace monitor {

template <typename... Args>
void workerLog(std::format_string<Args...> fmt, Args &&...args) {
    log("worker", fmt, std::forward<Args>(args)...);
}

} // namespace monitor

#endif