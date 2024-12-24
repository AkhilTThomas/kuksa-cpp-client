cmake_minimum_required(VERSION 3.15)
project(kuksaclient)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(gRPC REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(src)
add_subdirectory(example)

include(cmake/config.cmake)
