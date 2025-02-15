#********************************************************************************
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
#*******************************************************************************/

#!/usr/bin/env just --justfile
# This is a justfile. It's a handy way to organize shell commands.
# Also see: https://just.systems/man/en/

set dotenv-load := true
set shell := ["/bin/bash", "-c", "-l"]

default:
    @just --list

prepare:
    pip install conan==2.11.0
    conan remote add conancenter https://center.conan.io

configure:
    conan install . -pr:b conan/profile_x86_64_Release.txt -pr:h conan/profile_x86_64_Release.txt  --build=missing

build:
    conan build . -pr:b conan/profile_x86_64_Release.txt -pr:h conan/profile_x86_64_Release.txt

# run the databroker in a seperate windows
run-databroker:
    tmux new-window -n kuksa docker run --rm -it -p 55555:55555 -v $(pwd):/tmp ghcr.io/eclipse-kuksa/kuksa-databroker:main --insecure --vss /tmp/data/vss-core/vss_release_4.0.json

run-example-v2:
    just run-databroker
    tmux new-window -n example-v2 "./build/Release/bin/example_v2 || echo 'Process terminated. Press Enter to close.'; read"
