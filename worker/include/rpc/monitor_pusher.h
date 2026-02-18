#pragma once
#ifndef MONITOR_MONITOR_PUSHER_H
#define MONITOR_MONITOR_PUSHER_H

#include <atomic>
#include <condition_variable>
#include <grpcpp/grpcpp.h>
#include <mutex>
#include <thread>

#include "collector/info_collector.h"
#include "info_manager.grpc.pb.h"
#include "utils/worker_config.h"

namespace monitor {

class MonitorPusher {
public:
    explicit MonitorPusher(const WorkerConfig &config);
    ~MonitorPusher();

    void start();
    void stop();

private:
    void pushLoop();
    void push();

    WorkerConfig m_config;

    std::atomic_bool m_running;
    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cv;

    std::unique_ptr<monitor::InfoManager::Stub> m_stub;

    monitor::InfoCollector m_infoCollector;

    MonitorPusher(const MonitorPusher &) = delete;
    MonitorPusher &operator=(const MonitorPusher &) = delete;
};

} // namespace monitor

#endif