find_package(absl CONFIG REQUIRED)
message(STATUS "Found Abseil: ${absl_VERSION}")

set(SOURCES
	src/main.cpp

	src/rpc/monitor_pusher.cpp

	src/collector/info_collector.cpp
	src/collector/collector_interface.cpp
	src/collector/host_info_collector.cpp

	src/utils/display_monitor_info.cpp
)

add_executable(worker ${SOURCES})
target_link_libraries(worker PRIVATE
	monitor-proto
	absl::flags
    absl::flags_parse
)
target_include_directories(worker PRIVATE include)