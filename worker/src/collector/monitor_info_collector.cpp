#include "collector/monitor_info_collector.h"

#include "collector/host_info_collector.h"
#include "google/protobuf/util/time_util.h"

namespace monitor {

MonitorInfoCollector::MonitorInfoCollector() {
    m_collectors.emplace_back(std::make_unique<HostInfoCollector>());
}
MonitorInfoCollector::~MonitorInfoCollector() {}

MonitorInfo MonitorInfoCollector::collectInfo() {
    MonitorInfo monitorInfo;
    for (auto &collector : m_collectors) {
        collector->collectInfo(monitorInfo);
    }

    *monitorInfo.mutable_collecttime() =
        google::protobuf::util::TimeUtil::GetCurrentTime();

    return monitorInfo;
}

} // namespace monitor