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
    conan install . --build=missing

build:
    conan build .

# run the databroker in a seperate windows
run-databroker:
    tmux new-window -n kuksa docker run --rm -it -p 55555:55555 -v $(pwd):/tmp ghcr.io/eclipse-kuksa/kuksa-databroker:main --insecure --vss /tmp/data/vss-core/vss_release_4.0.json

run-example-v2:
    just run-databroker
    tmux new-window -n example-v2 "./build/Release/bin/example_v2 || echo 'Process terminated. Press Enter to close.'; read"
