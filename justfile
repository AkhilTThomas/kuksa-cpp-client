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
