cmake_minimum_required(VERSION 3.10)
project(monitor-system)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(proto)
add_subdirectory(common)
add_subdirectory(worker)
add_subdirectory(manager)