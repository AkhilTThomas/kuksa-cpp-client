# ****************************************************************************
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
# ****************************************************************************/

set(examples example_v1 example_v2)

foreach(example ${examples})
  add_executable(${example} ${example}.cpp)

  target_link_libraries(${example} kuksaclient)
  target_link_directories(${example} PRIVATE ${CMAKE_BINARY_DIR})
  target_include_directories(${example} PUBLIC ${PROJECT_SOURCE_DIR}/include)

  set_target_properties(${example} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                              ${CMAKE_BINARY_DIR}/bin)
endforeach()
