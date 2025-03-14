# *****************************************************************************
# Copyright (c) 2023 Contributors to the Eclipse Foundation
#
# See the NOTICE file(s) distributed with this work for additional information
# regarding copyright ownership.
#
# This program and the accompanying materials are made available under the terms
# of the Apache License 2.0 which is available at
# http://www.apache.org/licenses/LICENSE-2.0
#
# SPDX-License-Identifier: Apache-2.0
# *****************************************************************************/

cmake_minimum_required(VERSION 3.15)
project(kuksaclient)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(gRPC REQUIRED)
find_package(Protobuf REQUIRED)
find_package(spdlog REQUIRED)

include(cmake/config.cmake)

if(ENABLE_UNIT_TESTS STREQUAL "ON")
  include(CTest)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-arcs -ftest-coverage")
  # Required for gcovr
  find_package(Python3 REQUIRED COMPONENTS Interpreter)
  add_custom_target(
    coverage
    COMMAND ${CMAKE_COMMAND} -E make_directory coverage
    COMMAND ${Python3_EXECUTABLE} -m gcovr -r ${CMAKE_SOURCE_DIR} --html
            --html-nested -o coverage/index.html
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating HTML coverage report...")
  find_package(GTest REQUIRED)
  enable_testing()
  add_subdirectory(tests/unit/src)
endif()

add_subdirectory(src)
add_subdirectory(example)
