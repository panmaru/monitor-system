#pragma once
#ifndef MONITOR_MANAGER_SERVER_H
#define MONITOR_MANAGER_SERVER_H

#include <grpcpp/grpcpp.h>

#include "rpc/monitor_info_manager.h"
#include "utils/manager_config.h"

namespace monitor {

class ManagerServer {
public:
    ManagerServer(const ManagerConfig &managerConfig);
    ~ManagerServer();

    void start();
    void stop();

private:
    ManagerConfig m_config;
    MonitorInfoManager m_monitorInfoManager;
    std::unique_ptr<grpc::Server> m_server;

    ManagerServer(const ManagerServer &) = delete;
    ManagerServer &operator=(const ManagerServer &) = delete;
};

} // namespace monitor

#endif