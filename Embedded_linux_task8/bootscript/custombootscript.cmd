# Memory addresses
setenv kernel_addr_r 0x80000

# Boot Args

setenv bootargs "console=ttyS0,115200 8250.nr_uarts=1 loglevel=8 panic=5 rdinit=/dualpart_init "

printenv bootargs
echo ${bootargs}

# Kernel / DTB names
setenv kernel_image Image
setenv fdt_file bcm2710-rpi-3-b-plus.dtb
setenv ramdisk_file myInitramfs


echo "Trying to boot from SD card..."

if fatload mmc 0:1 ${kernel_addr_r} ${kernel_image}; then
    echo "Kernel loaded from SD card"

    if fatload mmc 0:1 ${fdt_addr_r} ${fdt_file}; then
        echo "DTB loaded from SD card"

        if fatload mmc 0:1 ${ramdisk_addr_r} ${ramdisk_file}; then
            echo "Initramfs loaded from SD card"
            booti ${kernel_addr_r} ${ramdisk_addr_r} ${fdt_addr_r}
        else
            echo "Initramfs not found, booting without ramfs"
            booti ${kernel_addr_r} - ${fdt_addr_r}
        fi

    else
        echo "DTB not found on SD card"
    fi
else
    echo "Kernel not found on SD card"
fi

echo "Trying to boot from TFTP..."

if tftp ${kernel_addr_r} ${kernel_image}; then
    echo "Kernel downloaded via TFTP"

    if tftp ${fdt_addr_r} ${fdt_file}; then
        echo "DTB downloaded via TFTP"

        if tftp ${ramdisk_addr_r} ${ramdisk_file}; then
            echo "Initramfs downloaded via TFTP"
            booti ${kernel_addr_r} ${ramdisk_addr_r} ${fdt_addr_r}
        else
            echo "Initramfs not found, booting without ramfs"
            booti ${kernel_addr_r} - ${fdt_addr_r}
        fi

    else
        echo "DTB download failed"
    fi
else
    echo "TFTP kernel download failed"
fi

echo "=================================="
echo "ERROR: Boot failed from SD and TFTP"
echo "=================================="