#ifndef KUKSACLIENT_H
#define KUKSACLIENT_H
#include "kuksa/val/v1/types.pb.h"
#include <kuksa/val/v1/val.grpc.pb.h>
#include <kuksa/val/v2/val.grpc.pb.h>
#include <memory>
#include <string>

namespace kuksa {

using kuksaCallbackV1 = std::function<void(
    const std::string &path, const kuksa::val::v1::Datapoint &value)>;
using kuksaCallbackV2 = std::function<void(const std::string &path,
                                           const kuksa::val::v2::Value &value)>;

class KuksaClient {
public:
  KuksaClient();
  ~KuksaClient();

  bool connect_v1(const std::string &server);
  bool connect_v2(const std::string &server);
  bool get(const std::string &datapoint, kuksa::val::v2::Value &value);
  bool get(const std::string &datapoint, kuksa::val::v1::Datapoint &value);
  bool set(const std::string &datapoint, kuksa::val::v2::Value const &value);
  bool set(const std::string &datapoint,
           kuksa::val::v1::Datapoint const &value);
  void subscribe(const std::vector<std::string> &datapoints,
                 kuksaCallbackV1 callback);
  void subscribe(const std::vector<std::string> &datapoints,
                 kuksaCallbackV2 callback);

private:
  class KuksaClientImpl;
  std::unique_ptr<KuksaClientImpl> mKuksaClient;
};
} // namespace kuksa
#endif // KUKSACLIENT_H
