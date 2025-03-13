/********************************************************************************
 * Copyright (c) 2022 Contributors to the Eclipse Foundation
 *
 * See the NOTICE file(s) distributed with this work for additional
 * information regarding copyright ownership.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License 2.0 which is available at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/
#include "kuksa/val/v1/types.pb.h"
#include "kuksa/val/v1/val.pb.h"
#include "kuksa/val/v2/types.pb.h"
#include "kuksa/val/v2/val.pb.h"
#include "kuksa_client_impl.h"
#include "kuksaclient.h"
#include <grpcpp/client_context.h>
#include <grpcpp/grpcpp.h>
#include <kuksa/val/v2/val.grpc.pb.h>
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <thread>
#include <vector>

namespace kuksa {

// Public interface implementations
KuksaClient::KuksaClient()
    : mKuksaClient(std::make_unique<KuksaClientImpl>()) {}

KuksaClient::KuksaClient(
    std::unique_ptr<kuksa::val::v2::VAL::StubInterface> stub)
    : mKuksaClient(std::make_unique<KuksaClientImpl>(std::move(stub))) {}

KuksaClient::~KuksaClient(){};

bool KuksaClient::connect_v1(const std::string &server) {
  return mKuksaClient->connect_v1(server);
}

bool KuksaClient::connect_v2(const std::string &server) {
  return mKuksaClient->connect_v2(server);
}

bool KuksaClient::get(const std::string &datapoint,
                      kuksa::val::v1::Datapoint &value) {
  return mKuksaClient->get(datapoint, value);
}

bool KuksaClient::getValue(const std::string &datapoint,
                           kuksa::val::v2::Value &value) {
  return mKuksaClient->getValue(datapoint, value);
}

bool KuksaClient::set(const std::string &datapoint,
                      const kuksa::val::v1::Datapoint &value) {
  return mKuksaClient->set(datapoint, value);
}

void KuksaClient::subscribe(const std::vector<std::string> &datapoints,
                            kuksaCallbackV1 callback) {
  return mKuksaClient->subscribe(datapoints, callback);
}

void KuksaClient::subscribe(const std::vector<std::string> &datapoints,
                            kuksaCallbackV2 callback) {
  return mKuksaClient->subscribe(datapoints, callback);
}

bool KuksaClient::actuate(const std::string &datapoint,
                          const kuksa::val::v2::Value &value) {
  return mKuksaClient->actuate(datapoint, value);
}

bool KuksaClient::publishValue(const std::string &datapoint,
                               const kuksa::val::v2::Value &value) {
  return mKuksaClient->publishValue(datapoint, value);
}

bool KuksaClient::getServerInfo(
    kuksa::val::v2::GetServerInfoResponse &response) {
  return mKuksaClient->getServerInfo(response);
}

std::vector<kuksa::val::v2::Datapoint>
KuksaClient::getValues(const std::vector<std::string> &datapoints) {
  return mKuksaClient->getValues(datapoints);
}
} // namespace kuksa
