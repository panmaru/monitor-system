#pragma once
#ifndef MONITOR_HOST_H
#define MONITOR_HOST_H

#include <format>
#include <ostream>

namespace monitor {

struct Host {
    std::string hostname;
    std::string ip;

    auto operator<=>(const Host &other) const = default;
    bool operator==(const Host &other) const = default;

    std::string toString() const { return std::format("{}@{}", hostname, ip); }

    friend std::ostream &operator<<(std::ostream &os,
                                    const monitor::Host &host);
};

} // namespace monitor

template <> struct std::hash<monitor::Host> {
    size_t operator()(const monitor::Host &host) const {
        size_t h1 = std::hash<std::string>()(host.hostname);
        size_t h2 = std::hash<std::string>()(host.ip);
        return h1 ^ (h2 << 1);
    }
};

template <> struct std::formatter<monitor::Host> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }
    auto format(const monitor::Host &host, std::format_context &ctx) const {
        return std::format_to(ctx.out(), "{}@{}", host.hostname, host.ip);
    }
};

#endif