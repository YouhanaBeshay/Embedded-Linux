#include "SevenSegment.hpp"
#include <iostream>

const u_int8_t DigitsLUT[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111,
                                0b01100110, 0b01101101, 0b01111101, 0b00000111,
                                0b01111111, 0b01101111};

SevenSegment::SevenSegment(std::array<mcal::gpio::Gpio_Pin_t, 7>& pins_num)
    : SevenSegment(pins_num, Common_t::COMMON_ANODE) // delegated constructor
{}
SevenSegment::SevenSegment(std::array<mcal::gpio::Gpio_Pin_t, 7>& pins_num,
                           Common_t common) {
  std::cout << "SevenSegment Constructor\n";
  common_ = common;
  for (int i = 0; i < 7; i++) {
    pins_[i] = std::make_unique<mcal::gpio::GPIO>(
        pins_num[i], mcal::gpio::Gpio_Direction_t::OUTPUT);
    if (common_ == Common_t::COMMON_ANODE) {
      pins_[i]->SetPin(mcal::gpio::Gpio_Value_t::HIGH);
    } else {
      pins_[i]->SetPin(mcal::gpio::Gpio_Value_t::LOW);
    }
  }
}
SevenSegment::~SevenSegment() { std::cout << "SevenSegment Destructor\n"; }

void SevenSegment::writeDigit(int digit) {
  if (digit != -1) {
    for (int i = 0; i < 7; i++) {
      if (DigitsLUT[digit] & (1 << i)) {
        // turn on the segment
        if (common_ == Common_t::COMMON_ANODE) {
          pins_[i]->SetPin(mcal::gpio::Gpio_Value_t::LOW);
        } else {
          pins_[i]->SetPin(mcal::gpio::Gpio_Value_t::HIGH);
        }

      } else {
        // turn off the segment
        if (common_ == Common_t::COMMON_ANODE) {
          pins_[i]->SetPin(mcal::gpio::Gpio_Value_t::HIGH);
        } else {
          pins_[i]->SetPin(mcal::gpio::Gpio_Value_t::LOW);
        }
      }
    }
  } else {
    // -1 =  error = turn off all segments
    for (int i = 0; i < 7; i++) {
      if (common_ == Common_t::COMMON_ANODE) {
        pins_[i]->SetPin(mcal::gpio::Gpio_Value_t::HIGH);
      } else {
        pins_[i]->SetPin(mcal::gpio::Gpio_Value_t::LOW);
      }
    }
  }
}

Stream &SevenSegment::operator<<(int digit) {
  writeDigit(digit);
  return *this; // for possible chaining
};