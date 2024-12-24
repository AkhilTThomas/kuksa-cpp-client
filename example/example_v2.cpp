#include <ostream>
#include <stdio.h>
#include <unistd.h>

#include "kuksaclient.h"
#include <kuksa/val/v2/types.pb.h>

using namespace kuksa;

void handleValue(const kuksa::val::v2::Value &value) {
  switch (value.typed_value_case()) {
  case kuksa::val::v2::Value::kString:
    std::cout << "String value: " << value.string() << std::endl;
    break;
  case kuksa::val::v2::Value::kBool:
    std::cout << "Bool value: " << value.bool_() << std::endl;
    break;
  case kuksa::val::v2::Value::kInt32:
    std::cout << "Int32 value: " << value.int32() << std::endl;
    break;
  case kuksa::val::v2::Value::kFloat:
    std::cout << "Float value: " << value.float_() << std::endl;
    break;
  case kuksa::val::v2::Value::kDouble:
    std::cout << "Double value: " << value.double_() << std::endl;
    break;
  default:
    std::cout << "Unsupported value type" << std::endl;
    break;
  }
}

void on_data_reception_v2(const std::string &path,
                          const kuksa::val::v2::Value &value) {
  std::cout << "Received " << path << std::endl;
  handleValue(value);
}

void on_data_reception_v1(const std::string &path,
                          const kuksa::val::v1::Datapoint &value) {
  std::cout << "Received " << path << std::endl;
}

int main() {
  std::cout << "Starting example for v2 ..." << std::endl;
  KuksaClient instance;
  bool connectionStatus = instance.connect_v2("127.0.0.1:55555");
  printf("Connection is %s \n",
         (connectionStatus == true) ? "Succesfull" : "Failed");
  sleep(2);

  kuksa::val::v2::Value value{};
  if (instance.get("Vehicle.Speed", value)) {
  }
  handleValue(value);
  sleep(1);

  value.set_float_(41.4f);

  std::cout << value.typed_value_case() << std::endl;
  instance.set("Vehicle.Speed", value);

  std::vector<std::string> signals = {"Vehicle.Speed", "Vehicle.Width"};

  instance.subscribe(signals, on_data_reception_v2);

  sleep(10);

  return 0;
}
