#include "Display.hpp"
#include <chrono>
#include <iostream>

void Display::DisplayTemperature(
    std::weak_ptr<hal::tempsensor::TemperatureReading_t> TempReading) {

  if (!TempReading.expired()) {

    auto DisplayReading = TempReading.lock();

    if (DisplayReading->Temperature != -1000.0) {
      std::cout << "Temperature: " << DisplayReading->Temperature << "°C"
                << std::endl;
        // The display only displays the temp not the timestamp 
        
    } else {
      // dont print anything if we couldnt read temperature
    }
  }
}