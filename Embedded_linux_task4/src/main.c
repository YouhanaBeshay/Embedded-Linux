#include "BCM2837.h"
#include <stdint.h>

#define GPIO_AF_REG_2  *((volatile uint32_t *)BCM2837_GPFSEL2)
#define GPIO_SET_REG_0  *((volatile uint32_t *)BCM2837_GPSET0)
#define GPIO_CLR_REG_0  *((volatile uint32_t *)BCM2837_GPCLR0)

int main()
{
    GPIO_AF_REG_2 &= ~(7 << 18); // clear bits 
    
    GPIO_AF_REG_2 |= (1 << 18); // set GPIO 26 to output  
    
    while (1)
    {
        GPIO_SET_REG_0 = (1 << 26); // set GPIO 26 high

        for (volatile int i = 0; i < 100000000; i++)
        {
            // do nothing
        }

        GPIO_CLR_REG_0 = (1 << 26); // set GPIO 26 low

        for ( volatile int i = 0; i < 100000000; i++)
        {
            // do nothing
        }

    }
    
    return 0;
}