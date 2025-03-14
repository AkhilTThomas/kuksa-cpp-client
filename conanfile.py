# ********************************************************************************
# Copyright (c) 2023 Contributors to the Eclipse Foundation
#
# See the NOTICE file(s) distributed with this work for additional
# information regarding copyright ownership.
#
# This program and the accompanying materials are made available under the
# terms of the Apache License 2.0 which is available at
# http://www.apache.org/licenses/LICENSE-2.0
#
# SPDX-License-Identifier: Apache-2.0
# *******************************************************************************/

from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout


class KuksaCppClient(ConanFile):
    name = "kuksa-cpp-client"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    options = {"enable_unit_tests": [True, False]}
    default_options = {"enable_unit_tests": False}

    def layout(self):
        cmake_layout(self)

    # Dependencies
    def requirements(self):
        self.requires("grpc/1.50.0")
        self.requires("spdlog/1.15.0")

    # Test dependencies
    def build_requirements(self):
        self.test_requires("gtest/1.16.0")

    # Building with CMake
    def build(self):
        cmake = CMake(self)
        variables = {
            "ENABLE_UNIT_TESTS": "ON" if self.options.enable_unit_tests else "OFF"
        }
        cmake.configure(variables=variables)
        cmake.build()
