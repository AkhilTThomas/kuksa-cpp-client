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

find_package(GTest REQUIRED)

add_executable(ut_kuksa test_basic.cpp)

target_include_directories(ut_kuksa PRIVATE ${PROJECT_SOURCE_DIR}/src/)

target_link_libraries(
  ut_kuksa PRIVATE kuksaclient GTest::gtest GTest::gtest_main GTest::gmock
                   GTest::gmock_main proto-objects)

# ensure test binary gets copied over to the binary folder
set_target_properties(ut_kuksa PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                          ${CMAKE_BINARY_DIR}/bin)

add_test(
  NAME UT_KUKSA
  COMMAND ut_kuksa
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
