#include "rpc/monitor_info_manager.h"

#include "utils/display_monitor_info.h"
#include "utils/manager_log.h"

namespace monitor {

grpc::Status
MonitorInfoManager::ReportMonitorInfo(grpc::ServerContext *context,
                                      const monitor::MonitorInfo *request,
                                      google::protobuf::Empty *response) {
    if (!request) {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                            "Invalid request");
    }

    if (!request->has_hostinfo()) {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                            "Missing host info");
    }

    Host host(request->hostinfo().hostname(), request->hostinfo().ipaddress());
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        m_infos[host] = *request;
    }

    managerLog("Received monitor info from {}", host);
    displayMonitorInfo(*request);

    return grpc::Status::OK;
}

} // namespace monitor