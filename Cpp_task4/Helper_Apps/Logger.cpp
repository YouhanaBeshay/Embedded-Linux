#include "Logger.hpp"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iomanip>

Logger::Logger(const std::string LogFile_Path)
    : LogFileFd_(
          open(LogFile_Path.c_str(), O_WRONLY | O_CREAT | O_APPEND,
               S_IRWXU)) // Write_read only, create if not exist ( with rwx
                         // permission to user) Append to orginal file
{}

Logger::~Logger() {
  if (LogFileFd_ != -1) {
    close(LogFileFd_);
  }
}

void Logger::LogTemperature(
    std::weak_ptr<hal::tempsensor::TemperatureReading_t> TempReading) {

  if (!TempReading.expired()) {

    auto LogReading = TempReading.lock();
    if (LogReading->Temperature != -1000.0) {

      // Logic to convert timestamp to string (Dont understand this quite yet)
      std::time_t t =
          std::chrono::system_clock::to_time_t(LogReading->TimeStamp);
      std::tm tm = *std::localtime(&t);

      std::ostringstream Timestamp_ostr; // output string to hold the timestamp
      Timestamp_ostr << std::put_time(&tm,
                           "%Y-%m-%d %H:%M:%S"); // put time into output string

      std::string fullLog = Timestamp_ostr.str() + "| Temperature: " +
                         std::to_string(LogReading->Temperature) + "°C\n";

      if (LogFileFd_ >= 0) {
        write(LogFileFd_, fullLog.c_str(), fullLog.size());
      }

    } else {
      // dont log anything if we couldnt read temperature
    }
  }
}