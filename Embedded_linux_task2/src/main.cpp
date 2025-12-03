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
    for (int i = 0; i < 10; i++)
    {
        sleep(1);
        myledpin.SetPin(mcal::gpio::Gpio_Value_t::HIGH);
        sleep(1);
        myledpin.SetPin(mcal::gpio::Gpio_Value_t::LOW);
    }
    
    std::cout << "Bye World!\n";


    
    return 0;
}
