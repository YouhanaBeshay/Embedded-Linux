#include "HAL/TempSensor.hpp"
#include "Helper_Apps/Display.hpp"
#include "Helper_Apps/Logger.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

constexpr int LogFrequency = 10; // log every 10 times the normal display time

int main() {
  // unique pointer to sensor, display and logger
  auto sensor =
      std::make_unique<hal::tempsensor::TempSensor>("/dev/ttyUSB0", 115200);
  auto DisplayObj = std::make_unique<Display>();
  auto LoggerObj = std::make_unique<Logger>("/home/youhana/tasks/Cpp_task4/TempLog.txt");

  // shared pointer to temperature reading
  auto TempReading = std::make_shared<hal::tempsensor::TemperatureReading_t>();

  unsigned int Log_counter = 0;

  while (1) {

    TempReading->Temperature = sensor->ReadTemperature();
    TempReading->TimeStamp = std::chrono::system_clock::now();

    DisplayObj->DisplayTemperature(TempReading);
    if (Log_counter == LogFrequency) {
      Log_counter = 0;
      LoggerObj->LogTemperature(TempReading);
    }
    Log_counter++;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  return 0;
}
