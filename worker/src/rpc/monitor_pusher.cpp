
#include "rpc/monitor_pusher.h"
#include "utils/display_monitor_info.h"
#include "utils/info.h"

namespace monitor {

MonitorPusher::MonitorPusher(const WorkerConfig &config)
    : m_config(config), m_running(false) {
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(
        config.managerAddress, grpc::InsecureChannelCredentials());
    m_stub = monitor::InfoManager::NewStub(channel);
}

MonitorPusher::~MonitorPusher() { stop(); }

void MonitorPusher::start() {
    if (m_running)
        return;

    m_running = true;
    m_thread = std::thread(&MonitorPusher::pushLoop, this);
    info("Monitor pusher started, pushing to {} every {} seconds",
         m_config.managerAddress, m_config.intervalSeconds);
}

void MonitorPusher::stop() {
    if (!m_running)
        return;

    m_running = false;
    m_cv.notify_one();
    if (m_thread.joinable())
        m_thread.join();
}

void MonitorPusher::pushLoop() {
    while (m_running) {
        info("Pushing worker info to manager...");
        push();

        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait_for(lock, std::chrono::seconds(m_config.intervalSeconds),
                      [this] { return !m_running; });
    }
}

void MonitorPusher::push() {
    monitor::MonitorInfo monitorInfo = m_infoCollector.collectInfo();
    displayMonitorInfo(monitorInfo);

    grpc::ClientContext context;
    google::protobuf::Empty response;
    grpc::Status status =
        m_stub->ReportMonitorInfo(&context, monitorInfo, &response);

    if (status.ok()) {
        info("Pushed monitor data to {} successfully", m_config.managerAddress);
    } else {
        info("Push failed: {}", status.error_message());
    }
}

} // namespace monitor