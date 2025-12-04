#include <mygpio.hpp>
#include <iostream>
#include <unistd.h> // for sleep
int main(int argc, char const *argv[])
{
    std::cout << "Hello World!\n";
    mcal::gpio::Gpio_Pin_t PinNumber = mcal::gpio::Gpio_Pin_t::GPIO_26;
    mcal::gpio::Gpio_Direction_t Direction = mcal::gpio::Gpio_Direction_t::OUTPUT;
    mcal::gpio::Gpio_Value_t Value = mcal::gpio::Gpio_Value_t::LOW;
    
    mcal::gpio::GPIO myledpin (PinNumber, Direction, Value  );
    int led_num = myledpin.GetPinNumber();
    std::cout << "led_num: " << led_num << "\n";
    int value = myledpin.GetPinValue();
    for (int i = 0; i < 6; i++)
    {
        sleep(1);
        myledpin.SetPin(mcal::gpio::Gpio_Value_t::HIGH);
        value = myledpin.GetPinValue();
        std::cout << "value: " << value << "\n";
        sleep(1);
        myledpin.SetPin(mcal::gpio::Gpio_Value_t::LOW);
        value = myledpin.GetPinValue();
        std::cout << "value: " << value << "\n";
    }
    
    std::cout << "Bye World!\n";


    
    return 0;
}
