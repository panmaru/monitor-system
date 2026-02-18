find_package(protobuf CONFIG REQUIRED)
message(STATUS "Found Protobuf: ${protobuf_VERSION}")

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Found gRPC: ${gRPC_VERSION}")

set(PROTO_FILES
	host_info.proto
	monitor_info.proto
	info_manager.proto
)

add_library(monitor-proto SHARED ${PROTO_FILES})
target_link_libraries(monitor-proto PUBLIC
	protobuf::libprotobuf
	gRPC::grpc++
)
target_include_directories(monitor-proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(GRPC_CPP_PLUGIN gRPC::grpc_cpp_plugin LOCATION)
if (NOT GRPC_CPP_PLUGIN)
	message(FATAL_ERROR "grpc_cpp_plugin not found")
endif()

protobuf_generate(TARGET monitor-proto LANGUAGE cpp)
protobuf_generate(TARGET monitor-proto
	LANGUAGE grpc
	GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
	PLUGIN "protoc-gen-grpc=${GRPC_CPP_PLUGIN}"
)