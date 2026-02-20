set(SOURCES
	src/utils/display_monitor_info.cpp
	src/utils/signal_handler.cpp
)

add_library(monitor-common STATIC ${SOURCES})
target_link_libraries(monitor-common PUBLIC monitor-proto)
target_include_directories(monitor-common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)