#pragma once
#ifndef MONITOR_MONITOR_INFO_MANAGER_H
#define MONITOR_MONITOR_INFO_MANAGER_H

#include <mutex>
#include <unordered_map>

#include "monitor_info_service.grpc.pb.h"
#include "utils/host.h"

namespace monitor {

class MonitorInfoManager final : public MonitorInfoService::Service {
public:
    MonitorInfoManager() = default;
    ~MonitorInfoManager() override = default;

    grpc::Status ReportMonitorInfo(grpc::ServerContext *context,
                                   const monitor::MonitorInfo *request,
                                   google::protobuf::Empty *response) override;

private:
    std::mutex m_mtx;
    std::unordered_map<Host, MonitorInfo> m_infos;

    MonitorInfoManager(const MonitorInfoManager &) = delete;
    MonitorInfoManager &operator=(const MonitorInfo &) = delete;
    MonitorInfoManager(MonitorInfoManager &&) = delete;
    MonitorInfoManager &operator=(MonitorInfoManager &&) = delete;
};

} // namespace monitor

#endif