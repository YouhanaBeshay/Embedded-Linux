# Buildroot Qt App:

## Part A : Create custom buildroot package
1. cd into buildroot directory
2. create a new package directory in `package/` directory
   - ```bash
     mkdir package/iti-qt-gpio
     ```
3. create `Config.in` file inside it
    - ```bash
        config BR2_PACKAGE_ITI_QT_GPIO
        bool "iti-qt-gpio"
        depends on BR2_PACKAGE_QT6BASE
        default y
        help
        A Qt6-based GPIO application.
        ```
4. create `iti-qt-gpio.mk` file inside it
    - ```bash
        ITI_QT_GPIO_VERSION = 1.0
        ITI_QT_GPIO_SITE = /home/youhana/iti_QT/REPO/QT_ITI/Task4_RpiLED 
        ITI_QT_GPIO_SITE_METHOD = local
        ITI_QT_GPIO_OVERRIDE_SRCDIR = /home/youhana/iti_QT/REPO/QT_ITI/Task4_RpiLED

        ITI_QT_GPIO_DEPENDENCIES = qt6base

        ITI_QT_GPIO_CONF_OPTS = \
            -DCMAKE_BUILD_TYPE=Release

        $(eval $(cmake-package))
        ```
5. Add to the `/package/Config.in` file:
    - ```bash
        source "package/iti-qt-gpio/Config.in"
         ```
## Part B: configure buildroot
1. configure buildroot using menuconfig
    - ```bash
        make menuconfig
        ```
    - <small> the already configuired `.config` is provided :)</small>
  
## Part C: build & send
1. build
    - ```bash
        make -j16
        ```

2. `dd` the image to the boot partition
    - ```bash
        dd if=buildroot/output/images/sdcard.img of=/dev/sda bs=16M 
        ```
3. add to the config.txt file
    - ```bash
        enable_uart=1
        dtoverlay=vc4-kms-v3d   # might be needed for physical display (havent tested yet)  
        hdmi_force_hotplug=1
        ```

## Part C : Cofigure the pi enviornment
1. make sure the qt looks for the correct fonts directory
    - ```bash
        export QT_QPA_FONTDIR=/usr/share/fonts
        ```
2. configure the rpi ip address
    - ```bash
        ip addr add 192.168.1.100/24 dev eth0
        ip link set eth0 up
        ```
3. Copy the fonts used to the pi ( we can do post install hook of the package but untill then we will do it manully)
    - ```bash
        scp /usr/share/fonts/truetype/ubuntu/*.ttf root@192.168.1.100:/usr/share/fonts/
        ```
4. run the app
    - ```bash
        cd /usr/bin/
        ./appTask4_RpiLED -platform vnc
        ```
5. open vnc to see the app

## DEMO VIDEO:

https://github.com/user-attachments/assets/c5b4f2f5-025f-47df-ab1d-380a30196d4f


