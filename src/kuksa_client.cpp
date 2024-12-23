#include "kuksa_client.h"
#include "kuksa/val/v2/val.pb.h"
#include <grpcpp/grpcpp.h>
#include <kuksa/val/v2/val.grpc.pb.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace kuksa {

const std::string loggerName = "kuksaClient";

class KuksaClient::KuksaClientImpl {
public:
  KuksaClientImpl() { mLogger = spdlog::stdout_color_mt(loggerName); }

  ~KuksaClientImpl() = default;

  bool connect(const std::string &server) {
    mLogger->info("Connect called on {}", server);
    mChannel = grpc::CreateChannel(server, grpc::InsecureChannelCredentials());
    mStub = kuksa::val::v2::VAL::NewStub(mChannel);

    auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(2);
    auto connected = mChannel->WaitForConnected(deadline);

    if (!connected) {
      mLogger->debug("Failed to connect to server within deadline");
      return false;
    }

    return true;
  }

  bool get(const std::string &datapoint, kuksa::val::v2::Value &value) {
    mLogger->info("get invoked on {}", datapoint);

    if (!mStub) {
      return false;
    }

    grpc::ClientContext context;
    kuksa::val::v2::GetValueRequest request;
    kuksa::val::v2::GetValueResponse response;

    request.mutable_signal_id()->set_path(datapoint);

    grpc::Status status = mStub->GetValue(&context, request, &response);

    if (!status.ok()) {
      mLogger->debug("RPC failed: {}", status.error_message());
      return false;
    }

    if (!response.has_data_point()) {
      mLogger->debug("Response has no data point");
      return false;
    }

    const auto &data_point = response.data_point();

    if (!data_point.has_value()) {
      mLogger->debug("Data point has no value");
      return false;
    }

    value = data_point.value();

    return true;
  }

  bool set(const std::string &datapoint, const kuksa::val::v2::Value &value) {
    mLogger->info("set invoked on {}", datapoint);

    if (!mStub) {
      mLogger->debug("Client not connected");
      return false;
    }

    grpc::ClientContext context;
    kuksa::val::v2::ActuateRequest request;
    kuksa::val::v2::ActuateResponse response;

    request.mutable_signal_id()->set_path(datapoint);
    *request.mutable_value() = value;

    grpc::Status status = mStub->Actuate(&context, request, &response);

    if (!status.ok()) {
      mLogger->debug("RPC failed: {}", status.error_message());
      return false;
    }

    return true;
  }

private:
  std::shared_ptr<grpc::Channel> mChannel;
  std::unique_ptr<kuksa::val::v2::VAL::Stub> mStub;
  std::shared_ptr<spdlog::logger> mLogger;
};

// Public interface implementations
KuksaClient::KuksaClient()
    : mKuksaClient(std::make_unique<KuksaClientImpl>()) {}

KuksaClient::~KuksaClient() = default;

bool KuksaClient::connect(const std::string &server) {
  return mKuksaClient->connect(server);
}

bool KuksaClient::get(const std::string &datapoint,
                      kuksa::val::v2::Value &value) {
  return mKuksaClient->get(datapoint, value);
}

bool KuksaClient::set(const std::string &datapoint,
                      const kuksa::val::v2::Value &value) {
  return mKuksaClient->set(datapoint, value);
}

} // namespace kuksa
