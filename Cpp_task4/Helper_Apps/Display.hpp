#pragma once
#include "../HAL/TempSensor.hpp"
#include <memory>

class Display {
private:
  /* data */
public:
  Display(/* args */) = default;
  ~Display() = default;

  void DisplayTemperature(
      std::weak_ptr<hal::tempsensor::TemperatureReading_t> TempReading);
};
