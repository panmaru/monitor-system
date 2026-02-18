#include "collector/info_collector.h"

#include "collector/host_info_collector.h"

namespace monitor {

InfoCollector::InfoCollector() {
    m_collectors.emplace_back(std::make_unique<HostInfoCollector>());
}
InfoCollector::~InfoCollector() {}

MonitorInfo InfoCollector::collectInfo() {
    MonitorInfo monitorInfo;
    for (auto &collector : m_collectors) {
        collector->collectInfo(monitorInfo);
    }
    return monitorInfo;
}

} // namespace monitor