#ifndef KUKSA_CLIENT_H
#define KUKSA_CLIENT_H
#include <kuksa/val/v2/val.grpc.pb.h>
#include <memory>
#include <string>

namespace kuksa {

class KuksaClient {
public:
  KuksaClient();
  ~KuksaClient();

  bool connect(const std::string &server);
  bool get(const std::string &datapoint, kuksa::val::v2::Value &value);
  bool set(const std::string &datapoint, kuksa::val::v2::Value const &value);

private:
  class KuksaClientImpl;
  std::unique_ptr<KuksaClientImpl> mKuksaClient;
};
} // namespace kuksa
#endif // KUKSA_CLIENT_H
