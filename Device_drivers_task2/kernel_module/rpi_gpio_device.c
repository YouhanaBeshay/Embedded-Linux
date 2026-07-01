#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/resource.h>

#include "inc/BCM2837.h"

static struct resource rpi_gpio_resources[] = {
    {
        .start = BCM2837_GPIO_BASE,           
        .end   = BCM2837_GPIO_BASE + BCM2837_GPIO_SIZE - 1,
        .flags = IORESOURCE_MEM,
    },
};

static struct platform_device rpi_gpio_device = {
    .name = "rpi-gpio",                // same as driver name
    .id   = -1,                        // single instance so we pass -1
    .resource = rpi_gpio_resources,
    .num_resources = ARRAY_SIZE(rpi_gpio_resources),
};

static int __init rpi_gpio_device_init(void)
{
    return platform_device_register(&rpi_gpio_device);
}

static void __exit rpi_gpio_device_exit(void)
{
    platform_device_unregister(&rpi_gpio_device);
}

module_init(rpi_gpio_device_init);
module_exit(rpi_gpio_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Youhana Beshay");
