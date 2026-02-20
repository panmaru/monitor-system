#pragma once
#ifndef MONITOR_MONITOR_INFO_REPORTER_H
#define MONITOR_MONITOR_INFO_REPORTER_H

#include <atomic>
#include <condition_variable>
#include <grpcpp/grpcpp.h>
#include <mutex>
#include <thread>

#include "collector/monitor_info_collector.h"
#include "monitor_info_service.grpc.pb.h"
#include "utils/worker_config.h"

namespace monitor {

class MonitorInfoReporter {
public:
    explicit MonitorInfoReporter(const WorkerConfig &config);
    ~MonitorInfoReporter();

    void start();
    void stop();

private:
    void reportLoop();
    void push();

    WorkerConfig m_config;

    std::atomic_bool m_running;
    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cv;

    std::unique_ptr<monitor::MonitorInfoService::Stub> m_stub;

    monitor::MonitorInfoCollector m_infoCollector;

    MonitorInfoReporter(const MonitorInfoReporter &) = delete;
    MonitorInfoReporter &operator=(const MonitorInfoReporter &) = delete;
};

} // namespace monitor

#endif