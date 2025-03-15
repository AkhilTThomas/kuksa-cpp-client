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

TEST(KuksaClientTest, getValue_failed) {
  auto mock_stub = std::make_unique<kuksa::val::v2::MockVALStub>();

  EXPECT_CALL(*mock_stub, GetValue)
      .WillOnce([](grpc::ClientContext *ctx,
                   const kuksa::val::v2::GetValueRequest &request,
                   kuksa::val::v2::GetValueResponse *response) -> grpc::Status {
        EXPECT_EQ(request.signal_id().path(), "Vehicle.Speed");
        return grpc::Status::CANCELLED;
      });

  kuksa::KuksaClient client(std::move(mock_stub));
  kuksa::val::v2::Value value{};
  bool status = client.getValue("Vehicle.Speed", value);

  EXPECT_FALSE(status);
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

TEST(KuksaClientTest, publish_value_failed) {
  auto mock_stub = std::make_unique<kuksa::val::v2::MockVALStub>();

  EXPECT_CALL(*mock_stub, PublishValue)
      .WillOnce(
          [](grpc::ClientContext *ctx,
             const kuksa::val::v2::PublishValueRequest &request,
             kuksa::val::v2::PublishValueResponse *response) -> grpc::Status {
            EXPECT_EQ(request.signal_id().path(), "Vehicle.Speed");
            EXPECT_EQ(request.data_point().value().float_(), 52.23f);
            return grpc::Status::CANCELLED;
          });

  kuksa::KuksaClient client(std::move(mock_stub));
  kuksa::val::v2::Value value{};
  value.set_float_(52.23f);
  bool status = client.publishValue("Vehicle.Speed", value);

  EXPECT_FALSE(status);
}

TEST(KuksaClientTest, actuate) {
  auto mock_stub = std::make_unique<kuksa::val::v2::MockVALStub>();

  EXPECT_CALL(*mock_stub, Actuate)
      .WillOnce([](grpc::ClientContext *ctx,
                   const kuksa::val::v2::ActuateRequest &request,
                   kuksa::val::v2::ActuateResponse *response) -> grpc::Status {
        EXPECT_EQ(request.signal_id().path(), "Vehicle.Body.Trunk.Rear.IsOpen");
        EXPECT_EQ(request.value().bool_(), true);
        return grpc::Status::OK;
      });

  kuksa::KuksaClient client(std::move(mock_stub));
  kuksa::val::v2::Value value{};
  value.set_bool_(true);
  bool status = client.actuate("Vehicle.Body.Trunk.Rear.IsOpen", value);

  EXPECT_TRUE(status);
}

TEST(KuksaClientTest, actuate_failed) {
  auto mock_stub = std::make_unique<kuksa::val::v2::MockVALStub>();

  EXPECT_CALL(*mock_stub, Actuate)
      .WillOnce([](grpc::ClientContext *ctx,
                   const kuksa::val::v2::ActuateRequest &request,
                   kuksa::val::v2::ActuateResponse *response) -> grpc::Status {
        EXPECT_EQ(request.signal_id().path(), "Vehicle.Body.Trunk.Rear.IsOpen");
        EXPECT_EQ(request.value().bool_(), true);
        return grpc::Status::CANCELLED;
      });

  kuksa::KuksaClient client(std::move(mock_stub));
  kuksa::val::v2::Value value{};
  value.set_bool_(true);
  bool status = client.actuate("Vehicle.Body.Trunk.Rear.IsOpen", value);

  EXPECT_FALSE(status);
}

TEST(KuksaClientTest, getServerInfo) {
  auto mock_stub = std::make_unique<kuksa::val::v2::MockVALStub>();

  EXPECT_CALL(*mock_stub, GetServerInfo)
      .WillOnce(
          [](grpc::ClientContext *ctx,
             const kuksa::val::v2::GetServerInfoRequest &request,
             kuksa::val::v2::GetServerInfoResponse *response) -> grpc::Status {
            *response->mutable_name() = "kuksa_gtest_mock";
            *response->mutable_version() = "1.2.3";
            *response->mutable_commit_hash() = "123456789abcdefg";
            return grpc::Status::OK;
          });

  kuksa::KuksaClient client(std::move(mock_stub));

  kuksa::val::v2::GetServerInfoResponse serverInfo{};
  bool status = client.getServerInfo(serverInfo);

  EXPECT_TRUE(status);
  EXPECT_EQ(serverInfo.name(), "kuksa_gtest_mock");
  EXPECT_EQ(serverInfo.version(), "1.2.3");
  EXPECT_EQ(serverInfo.commit_hash(), "123456789abcdefg");
}

TEST(KuksaClientTest, getServerInfo_failed) {
  auto mock_stub = std::make_unique<kuksa::val::v2::MockVALStub>();

  EXPECT_CALL(*mock_stub, GetServerInfo)
      .WillOnce(
          [](grpc::ClientContext *ctx,
             const kuksa::val::v2::GetServerInfoRequest &request,
             kuksa::val::v2::GetServerInfoResponse *response) -> grpc::Status {
            *response->mutable_name() = "kuksa_gtest_mock";
            *response->mutable_version() = "1.2.3";
            *response->mutable_commit_hash() = "123456789abcdefg";
            return grpc::Status::CANCELLED;
          });

  kuksa::KuksaClient client(std::move(mock_stub));

  kuksa::val::v2::GetServerInfoResponse serverInfo{};
  bool status = client.getServerInfo(serverInfo);

  EXPECT_FALSE(status);
}

TEST(KuksaClientTest, getValues) {
  auto mock_stub = std::make_unique<kuksa::val::v2::MockVALStub>();

  EXPECT_CALL(*mock_stub, GetValues)
      .WillOnce(
          [](grpc::ClientContext *ctx,
             const kuksa::val::v2::GetValuesRequest &request,
             kuksa::val::v2::GetValuesResponse *response) -> grpc::Status {
            EXPECT_EQ(request.signal_ids(0).path(), "Vehicle.Speed");
            EXPECT_EQ(request.signal_ids(1).path(),
                      "Vehicle.Chassis.Accelerator.PedalPosition");

            auto dp1 = response->add_data_points();
            dp1->mutable_value()->set_float_(42.35f);

            auto dp2 = response->add_data_points();
            dp2->mutable_value()->set_uint32(67);

            return grpc::Status::OK;
          });

  kuksa::KuksaClient client(std::move(mock_stub));

  std::vector<kuksa::val::v2::Datapoint> datapoints;
  std::vector<std::string> signals = {
      "Vehicle.Speed", "Vehicle.Chassis.Accelerator.PedalPosition"};

  datapoints = client.getValues(signals);

  EXPECT_EQ(datapoints.at(0).value().float_(), 42.35f);
  EXPECT_EQ(datapoints.at(1).value().uint32(), 67);
}

TEST(KuksaClientTest, getValues_failed) {
  auto mock_stub = std::make_unique<kuksa::val::v2::MockVALStub>();

  EXPECT_CALL(*mock_stub, GetValues)
      .WillOnce(
          [](grpc::ClientContext *ctx,
             const kuksa::val::v2::GetValuesRequest &request,
             kuksa::val::v2::GetValuesResponse *response) -> grpc::Status {
            EXPECT_EQ(request.signal_ids(0).path(), "Vehicle.Speed");
            EXPECT_EQ(request.signal_ids(1).path(),
                      "Vehicle.Chassis.Accelerator.PedalPosition");

            return grpc::Status::CANCELLED;
          });

  kuksa::KuksaClient client(std::move(mock_stub));

  std::vector<kuksa::val::v2::Datapoint> datapoints;
  std::vector<std::string> signals = {
      "Vehicle.Speed", "Vehicle.Chassis.Accelerator.PedalPosition"};

  datapoints = client.getValues(signals);

  // expect empty vector
  EXPECT_EQ(0, datapoints.size());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
