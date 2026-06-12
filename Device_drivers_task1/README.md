# Device Drivers Task 1

- Creating a procfs device driver that controls a led on a raspberry pi 3 b+.


## Notes
  
  - **Makefile**:
    - Decided to use the kernel source provided by my previous Yocto build for easy testing on pi.
    ```bash
        # yocto kernel dir
        KDIR := /home/youhana/YOCTO/Yocto_WS/share/tmp/work/raspberrypi3_64-oe-linux/linux-raspberrypi/6.6.63+git/linux-raspberrypi3_64-standard-build

        # cross compiler
        ARCH := arm64
        CROSS_COMPILE := /home/youhana/x-tools/aarch64-rpi3-linux-gnu/bin/aarch64-rpi3-linux-gnu-
    ```
- **Userspace App**:
  - Went a bit beyond the scope of the task and did a simple Ros2 node with 2 Services:
    - `gpio_on` to turn the led on
    - `gpio_off` to turn the led off

## Output:

https://github.com/user-attachments/assets/a9184eda-da5b-4db9-b635-ed3cafd2a2ac

