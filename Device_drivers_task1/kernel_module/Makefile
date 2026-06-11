obj-m += rpi_gpio_module.o

# yocto kernel dir
KDIR := /home/youhana/YOCTO/Yocto_WS/share/tmp/work/raspberrypi3_64-oe-linux/linux-raspberrypi/6.6.63+git/linux-raspberrypi3_64-standard-build

# cross compiler
ARCH := arm64
CROSS_COMPILE := /home/youhana/x-tools/aarch64-rpi3-linux-gnu/bin/aarch64-rpi3-linux-gnu-


all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean