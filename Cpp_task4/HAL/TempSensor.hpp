
#pragma once
#include <string>
#include <chrono>

namespace hal {
namespace tempsensor {

struct TemperatureReading_t {
  float Temperature;
  std::chrono::system_clock::time_point TimeStamp;
}; // to be used in  other modules or main


class TempSensor {
private:
  int UartFd_ = -1;
  int BaudRate_ = 115200;

public:
  TempSensor(const std::string UartFile_Path, const int BaudRate);
  ~TempSensor();
  float ReadTemperature();
};

} // namespace tempsensor

} // namespace hal
