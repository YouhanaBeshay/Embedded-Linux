
#include "TempSensor.hpp"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace hal {
namespace tempsensor {

TempSensor::TempSensor(const std::string UartFile_Path, const int BaudRate)
    : UartFd_(open(UartFile_Path.c_str(),
                   O_RDONLY |
                       O_NOCTTY)), // Read only and no contrlling tty -NOCTTY-
                                   // (treats this file as just a normal file) ,
      BaudRate_(BaudRate) {
  // Configure UART using command "stty" (as alternative is somewhat complicated
  // :D)
  std::string command =
      "stty -F " + UartFile_Path + " " + std::to_string(BaudRate);
  system(command.c_str()); // execute the command
}

TempSensor::~TempSensor() {
  if (UartFd_ != -1) {
    close(UartFd_);
  }
}

float TempSensor::ReadTemperature() {
  float temp = -1000.0; // default return value (indicates some error)

  std::string tempStr; // temporary string to store file reading (as i dont know
                       // how much data i will read)
  char c;
  while (read(UartFd_, &c, 1) == 1) // read file char by char
  {
    if (c != '\n') {
      tempStr += c; // append character if not newline
    } else {
      break;
    }
  }

  // convert string to float only if its not empty
  if (!tempStr.empty()) {
    temp = std::stof(tempStr);
  }

  return temp;
}

} // namespace tempsensor

} // namespace hal
