#include <chrono>
#include <stdio.h>
#include <thread>
#include <unistd.h>

#include "kuksa_client.h"
#include <kuksa/val/v2/val.grpc.pb.h>

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

int main() {
  printf("Starting example ... \n");
  KuksaClient instance;
  instance.connect("127.0.0.1:55555");
  sleep(2);
  kuksa::val::v2::Value value{};
  // if (instance.get("Vehicle.Speed", value)) {
  // }
  // handleValue(value);
  // sleep(1);
  value.set_float_(41.4f);
  std::cout << value.typed_value_case() << std::endl;
  instance.set("Vehicle.Speed", value);

  return 0;
}
