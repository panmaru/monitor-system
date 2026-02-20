find_package(absl CONFIG REQUIRED)
get_target_property(ABSL_BASE_LOCATION absl::base LOCATION)
message(STATUS "Found Abseil: ${ABSL_BASE_LOCATION} (found version \"${absl_VERSION}\")")

set(SOURCES
	src/main.cpp

	src/rpc/monitor_info_reporter.cpp

	src/collector/monitor_info_collector.cpp
	src/collector/collector_interface.cpp
	src/collector/host_info_collector.cpp
)

add_executable(worker ${SOURCES})
target_link_libraries(worker PRIVATE
	monitor-common
	absl::flags
    absl::flags_parse
)
target_include_directories(worker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)