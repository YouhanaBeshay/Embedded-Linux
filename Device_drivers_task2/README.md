# Device Drivers Task 2

- RPi GPIO Platform Character Device Driver

A minimal Linux platform driver that exposes Raspberry Pi GPIO pin 26 as a `/dev` character device.

## Overview

- **Driver type**: Platform driver with character device interface
- **Target**: BCM2837 (Raspberry Pi 3) GPIO block
- **Interface**: `/dev/rpi_gpio` — read/write single byte (`0` or `1`)
- **Architecture**: Per-device data (`struct rpi_gpio_drvdata`) with `devm_*` managed resources

## What It Does

| Operation | Effect |
|-----------|--------|
| `echo 1 > /dev/rpi_gpio` | Sets GPIO 26 HIGH |
| `echo 0 > /dev/rpi_gpio` | Sets GPIO 26 LOW |
| `cat /dev/rpi_gpio` | Reads back last written value (`0` or `1`) |

## Architecture

```
User Space
    │
    ▼
/dev/rpi_gpio  ──►  struct file_operations  ──►  rpi_gpio_drvdata
    │                    (open/read/write)         ├── gpio_base (ioremap)
    │                                              ├── cdev
    │                                              ├── my_mutex 
    │                                              └── gpio_current_char
    ▼
Platform Bus
    │
    ├── Platform Device (rpi_gpio_device.ko)
    │      └── Resource: mem 0x3f200000-0x3f20009f
    │
    └── Platform Driver (rpi_gpio_driver.ko)
           ├── probe()  → ioremap, cdev_add, device_create
           └── remove() → cdev_del, device_destroy
```

## Files

| File | Purpose |
|------|---------|
| `rpi_gpio_driver.c` | Platform driver + character device logic |
| `rpi_gpio_device.c` | Legacy platform device (registers hardware description) |
| `Makefile` | Out-of-tree kernel module build |

## Build

```bash
make

sudo cp rpi_gpio_driver.ko rpi_gpio_device.ko <the_sd_card_root>
```

## Load

```bash
# 1. Register the device (hardware description)
insmod rpi_gpio_device.ko

# 2. Register the driver (binds to device, creates /dev/rpi_gpio)
insmod rpi_gpio_driver.ko

# 3. Verify
ls -l /dev/rpi_gpio
dmesg | tail
```

## Unload

```bash
rmmod rpi_gpio_driver
rmmod rpi_gpio_device
```

## Key Design Decisions

- **Per-device data**: `struct rpi_gpio_drvdata` holds all instance state, allowing multiple GPIO devices if extended.
- **devm_* resources**: `devm_kzalloc`, `devm_ioremap` auto-clean on probe failure or remove.
- **cdev + class**: Modern character device registration with automatic `/dev` node creation via udev.
- **container_of**: Retrieves per-device data from `inode->i_cdev` in `open()`, cached in `file->private_data`.

## output


https://github.com/user-attachments/assets/ebf14dc6-1c87-4c5b-87f4-c72b990f1ace


