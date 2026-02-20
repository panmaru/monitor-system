#include "server/manager_server.h"

namespace monitor {

ManagerServer::ManagerServer(const ManagerConfig &config) : m_config(config) {}

ManagerServer::~ManagerServer() { stop(); }

void ManagerServer::start() {
    grpc::ServerBuilder builder;
    builder.AddListeningPort(m_config.listenAddress,
                             grpc::InsecureServerCredentials());
    builder.RegisterService(&m_monitorInfoManager);
    m_server = builder.BuildAndStart();
}

void ManagerServer::stop() {
    if (m_server) {
        m_server->Shutdown();
        m_server.reset();
    }
}

} // namespace monitor