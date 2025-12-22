#pragma once

#include "mygpio.hpp"
#include "Istream.hpp"
#include "Ostream.hpp"

#include <array>
#include <memory>

enum class Common_t {
  COMMON_CATHODE,
  COMMON_ANODE,
};
class SevenSegment : public Istream, public Ostream {
private:
  Common_t common_ ;
  std::array<std::unique_ptr<mcal::gpio::GPIO>, 7>
      pins_; // array of pointer to gpio pins
            // as the gpio has no move or copy contsructors so we must use
            // pointers to it
public:
  // defualt treats it as COMMON_ANODE
  SevenSegment(std::array<mcal::gpio::Gpio_Pin_t, 7>& pins);

  SevenSegment(std::array<mcal::gpio::Gpio_Pin_t, 7>& pins, Common_t common);

  ~SevenSegment();
  void writeDigit(int digit) override;

  Stream &operator<<(int digit) override;
};
