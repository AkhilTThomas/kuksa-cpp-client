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
#ifndef KUKSA_CLIENT_IMPL_H
#define KUKSA_CLIENT_IMPL_H

#include "kuksa/val/v1/types.pb.h"
#include "kuksa/val/v1/val.pb.h"
#include "kuksa/val/v2/types.pb.h"
#include "kuksa/val/v2/val.pb.h"
#include "kuksaclient.h"
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/grpcpp.h>
#include <kuksa/val/v2/val.grpc.pb.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <thread>
#include <vector>

namespace kuksa {

class KuksaClient::KuksaClientImpl {
public:
  KuksaClientImpl();
  explicit KuksaClientImpl(
      std::unique_ptr<kuksa::val::v2::VAL::StubInterface> stub);
  ~KuksaClientImpl();

  // --------------------------- V1 APIs -------------------------------
  bool connect_v1(const std::string &server);
  bool get(const std::string &datapoint, kuksa::val::v1::Datapoint &value);
  bool set(const std::string &datapoint,
           const kuksa::val::v1::Datapoint &value);
  void subscribe(const std::vector<std::string> &datapoints,
                 kuksaCallbackV1 callback);

  // --------------------------- V2 APIs -------------------------------
  bool connect_v2(const std::string &server);
  bool getValue(const std::string &datapoint, kuksa::val::v2::Value &value);
  void subscribe(const std::vector<std::string> &datapoints,
                 kuksaCallbackV2 callback);
  bool actuate(const std::string &datapoint,
               const kuksa::val::v2::Value &value);
  bool publishValue(const std::string &datapoint,
                    const kuksa::val::v2::Value &value);
  bool getServerInfo(kuksa::val::v2::GetServerInfoResponse &response);
  std::vector<kuksa::val::v2::Datapoint>
  getValues(const std::vector<std::string> &datapoints);

private:
  std::shared_ptr<grpc::Channel> mChannel;
  std::unique_ptr<kuksa::val::v1::VAL::StubInterface> mStubV1;
  std::unique_ptr<kuksa::val::v2::VAL::StubInterface> mStubV2;
  std::shared_ptr<spdlog::logger> mLogger;
  std::thread mSubscribeThread;
  std::atomic<bool> mIsRunning;
};

} // namespace kuksa

#endif // KUKSA_CLIENT_IMPL_H
