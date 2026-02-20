find_package(protobuf CONFIG REQUIRED)
get_target_property(LIBPROTOBUF_LOCATION protobuf::libprotobuf LOCATION)
message(STATUS "Found Protobuf: ${LIBPROTOBUF_LOCATION} (found version \"${protobuf_VERSION}\")")

find_package(gRPC CONFIG REQUIRED)
get_target_property(GRPC_LOCATION gRPC::grpc LOCATION)
message(STATUS "Found gRPC: ${GRPC_LOCATION} (found version \"${gRPC_VERSION}\")")

set(PROTO_FILES
	host_info.proto
	monitor_info.proto
	monitor_info_service.proto
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