#include "collector/host_info_collector.h"

#include <ifaddrs.h>
#include <net/if.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>

#include "monitor_info.pb.h"

namespace monitor {

std::string HostInfoCollector::getHostname() {
    static char hostname[HOST_NAME_MAX + 1];
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        return "unknown";
    }
    return hostname;
}

std::string HostInfoCollector::getIpAddress() {
    ifaddrs *ifaddr;
    if (getifaddrs(&ifaddr) == -1) {
        return "unknown";
    }

    std::string ipAddress = "unknown";
    for (ifaddrs *ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr) {
            continue;
        }

        // Skip loopback
        if (ifa->ifa_flags & IFF_LOOPBACK) {
            continue;
        }

        // Skip down
        if (!(ifa->ifa_flags & IFF_UP)) {
            continue;
        }

        // Only IPv4
        if (ifa->ifa_addr->sa_family != AF_INET) {
            continue;
        }

        char host[NI_MAXHOST];
        if (getnameinfo(ifa->ifa_addr, sizeof(sockaddr_in), host, NI_MAXHOST,
                        nullptr, 0, NI_NUMERICHOST) == 0) {
            ipAddress = host;
            break;
        }
    }

    return ipAddress;
}

void HostInfoCollector::collectInfo(MonitorInfo &monitorInfo) {
    monitorInfo.mutable_hostinfo()->set_hostname(getHostname());
    monitorInfo.mutable_hostinfo()->set_ipaddress(getIpAddress());
}

void HostInfoCollector::stop() {}

} // namespace monitor