#pragma once
#include "../HAL/TempSensor.hpp"
#include <memory>
#include <string>

class Logger {
private:
  int LogFileFd_;


public:
  Logger(std::string LogFile_Path);
  ~Logger();
  void LogTemperature(
      std::weak_ptr<hal::tempsensor::TemperatureReading_t> TempReading);
};
