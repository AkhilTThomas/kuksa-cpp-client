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
#include "kuksa/val/v2/val.pb.h"
#include "kuksa/val/v2/val_mock.grpc.pb.h"
#include "kuksaclient.h"
#include "gmock/gmock.h"
#include <chrono>
#include <gmock/gmock.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/support/status.h>
#include <gtest/gtest.h>
#include <memory>
#include <spdlog/spdlog.h>

using ::testing::_;
using ::testing::Return;

TEST(KuksaClientTest, getValue) {
  auto mock_stub = std::make_unique<kuksa::val::v2::MockVALStub>();

  EXPECT_CALL(*mock_stub, GetValue)
      .WillOnce([](grpc::ClientContext *ctx,
                   const kuksa::val::v2::GetValueRequest &request,
                   kuksa::val::v2::GetValueResponse *response) -> grpc::Status {
        EXPECT_EQ(request.signal_id().path(), "Vehicle.Speed");
        response->mutable_data_point()->mutable_value()->set_float_(12.23f);
        return grpc::Status::OK;
      });

  kuksa::KuksaClient client(std::move(mock_stub));
  kuksa::val::v2::Value value{};
  bool status = client.getValue("Vehicle.Speed", value);

  EXPECT_TRUE(status);
  EXPECT_EQ(value.float_(), 12.23f);
}

TEST(KuksaClientTest, publish_value) {
  auto mock_stub = std::make_unique<kuksa::val::v2::MockVALStub>();

  EXPECT_CALL(*mock_stub, PublishValue)
      .WillOnce(
          [](grpc::ClientContext *ctx,
             const kuksa::val::v2::PublishValueRequest &request,
             kuksa::val::v2::PublishValueResponse *response) -> grpc::Status {
            EXPECT_EQ(request.signal_id().path(), "Vehicle.Speed");
            EXPECT_EQ(request.data_point().value().float_(), 52.23f);
            return grpc::Status::OK;
          });

  kuksa::KuksaClient client(std::move(mock_stub));
  kuksa::val::v2::Value value{};
  value.set_float_(52.23f);
  bool status = client.publishValue("Vehicle.Speed", value);

  EXPECT_TRUE(status);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
