#include "IOstream.hpp"
#include "SevenSegment.hpp"
#include "Stream.hpp"
#include <array>
#include <memory>

int main(int argc, char const *argv[]) {

  std::array<mcal::gpio::Gpio_Pin_t, 7> pins = {
      mcal::gpio::Gpio_Pin_t::GPIO_26, mcal::gpio::Gpio_Pin_t::GPIO_19,
      mcal::gpio::Gpio_Pin_t::GPIO_13, mcal::gpio::Gpio_Pin_t::GPIO_6,
      mcal::gpio::Gpio_Pin_t::GPIO_5,  mcal::gpio::Gpio_Pin_t::GPIO_0,
      mcal::gpio::Gpio_Pin_t::GPIO_11};

  std::unique_ptr<SevenSegment> ptr2 = std::make_unique<SevenSegment>(
      pins, Common_t::COMMON_ANODE);
  int digit = 0;

  // digit is automatically -1 if the input is invalid (not a digit from 0-9)
  while (digit != -1) {

    *ptr2 >> digit;
    *ptr2 << digit;
  }

  return 0;
}
