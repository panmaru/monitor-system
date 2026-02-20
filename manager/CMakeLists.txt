find_package(absl CONFIG REQUIRED)
get_target_property(ABSL_BASE_LOCATION absl::base LOCATION)
message(STATUS "Found Abseil: ${ABSL_BASE_LOCATION} (found version \"${absl_VERSION}\")")

set(SOURCES
	src/main.cpp

	src/rpc/monitor_info_manager.cpp

	src/server/manager_server.cpp

	src/utils/host.cpp
)

add_executable(manager ${SOURCES})
target_link_libraries(manager PRIVATE
	monitor-common
	absl::flags
	absl::flags_parse

)
target_include_directories(manager PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)