# Bare-Metal Programming : Loading and Running a Custom Binary from U-Boot

## Demo vid:

https://github.com/user-attachments/assets/068a7892-60b9-4ea4-a37d-bb50c2e5e405


## Part A : Preparing the Raspberry Pi boot partition

1. Get for  RPi the Needed Firmware Files:
   - from `https://github.com/raspberrypi/firmware`
    - copy the following files:
      - `bootcode.bin`
      - `start.elf`
      - `fixup.dat`
      - `bcm2710-rpi-3-b.dtb` <small>(or use the one in the linux repo `arch/arm64/boot/dts/`)</small> 
2. Create the `config.txt` file:
    - ```
        arm_64bit=1
        kernel=u-boot.bin
        enable_uart=1
        dtoverlay=disable-bt
        ```
3. Copy the u-boot files to the boot partition:
    - ` u-boot.bin`

4. copy all the files + bare-metal program (`youhana_blinky.img`) to the SD card


## Part B : connecting the Raspberry Pi to the network

1. Connect the Raspberry Pi to the laptop (ethernet cable)
2. set the ip for pc
3. set the ip & serverip for the raspberry pi (done in u-boot)
4. connect the raspberry pi with TTL to the laptop (USB-TTL)

## Part C : Entering  u-boot:

1. `sudo minicom -b 115200 /dev/ttyUSB0` <small> or use the `picocom` </small>

2. `fatload mmc 0:1 ${kernel_addr_r} youhana_blinky.img` <small> (or laod from tftp)</small>
3. `go ${kernel_addr_r}`

---
## Questions:
- Q1 : Brief explanation of the load address you chose and why? 
  -  I chose 0x80000 becuase 
     1. its a non preserved address
     2. its the default kernel address in uboot ${kernel_addr_r} so I dont need to modify it
- Q2 : Why do we need a startup.s file at all? Can’t we just write everything in
C?

  -  we need a startup.s file becuase it gives defines the _start which is the entry point in linkerscript & other initializations
  -  we need to write in assembly to configure the "sp" stack pointer which we cant access in C
