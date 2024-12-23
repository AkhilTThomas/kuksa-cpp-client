# CPP based Kuksa client

A pluggable Cpp based library to talk to [kuksa-databroker](https://github.com/eclipse-kuksa/kuksa-databroker)
based on v2 API

APIs

- `connect("127.0.0.1:55555")`
    Establish connection to a databroker end-point
- `get("Vehicle.Speed")`
    Get a datapoint value
- `set("Vehicle.Speed",value)`
    Set a datapoint with the corresponding value

## How to build

This repo contains a [justfile](https://github.com/casey/just) to help in
setting up and installing dependencies

```shell
# Install conan and setup remote
just prepare
# pull in the conan deps
just configure
# build the project
just build
```

## Proto

Proto sources are taken from the [repo](https://github.com/eclipse-kuksa/kuksa-databroker/tree/main/proto)

## Example

[example](example/example.cpp)
