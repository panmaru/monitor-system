
#include "rpc/monitor_info_reporter.h"
#include "utils/display_monitor_info.h"
#include "utils/worker_log.h"

namespace monitor {

MonitorInfoReporter::MonitorInfoReporter(const WorkerConfig &config)
    : m_config(config), m_running(false) {
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(
        config.managerAddress, grpc::InsecureChannelCredentials());
    m_stub = monitor::MonitorInfoService::NewStub(channel);
}

MonitorInfoReporter::~MonitorInfoReporter() { stop(); }

void MonitorInfoReporter::start() {
    if (m_running)
        return;

    m_running = true;
    m_thread = std::thread(&MonitorInfoReporter::reportLoop, this);
    workerLog("Monitor pusher started, pushing to {} every {} seconds",
              m_config.managerAddress, m_config.intervalSeconds);
}

void MonitorInfoReporter::stop() {
    if (!m_running)
        return;

    m_running = false;
    m_cv.notify_one();
    if (m_thread.joinable())
        m_thread.join();
}

void MonitorInfoReporter::reportLoop() {
    while (m_running) {
        workerLog("Pushing worker info to manager...");
        push();

        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait_for(lock, std::chrono::seconds(m_config.intervalSeconds),
                      [this] { return !m_running; });
    }
}

void MonitorInfoReporter::push() {
    monitor::MonitorInfo monitorInfo = m_infoCollector.collectInfo();
    displayMonitorInfo(monitorInfo);

    grpc::ClientContext context;
    google::protobuf::Empty response;
    grpc::Status status =
        m_stub->ReportMonitorInfo(&context, monitorInfo, &response);

    if (status.ok()) {
        workerLog("Pushed monitor data to {} successfully",
                  m_config.managerAddress);
    } else {
        workerLog("Push failed: {}", status.error_message());
    }
}

} // namespace monitor