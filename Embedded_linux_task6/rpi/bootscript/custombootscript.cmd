# Memory addresses
setenv kernel_addr_r 0x80000

# Boot Args

setenv bootargs "console=ttyAMA0,115200 earlycon=pl011,0x3f201000 loglevel=8 panic=5 \
                root=/dev/nfs rootwait rw rootdelay=3 \
                ip=192.168.1.20:::255.255.255.0:youhana_rpi:eth0:off \
                nfsroot=192.168.1.50:/home/youhana/example_rootfs,nfsvers=3,tcp" 


printenv bootargs
echo ${bootargs}

# Kernel / DTB names
setenv kernel_image Image
setenv fdt_file bcm2710-rpi-3-b-plus.dtb

echo "Trying to boot from SD card..."

if fatload mmc 0:1 ${kernel_addr_r} ${kernel_image}; then
    echo "Kernel loaded from SD card"

    if fatload mmc 0:1 ${fdt_addr_r} ${fdt_file}; then
        echo "DTB loaded from SD card"
        booti ${kernel_addr_r} - ${fdt_addr_r}
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
        booti ${kernel_addr_r} - ${fdt_addr_r}
    else
        echo "DTB download failed"
    fi
else
    echo "TFTP kernel download failed"
fi

echo "=================================="
echo "ERROR: Boot failed from SD and TFTP"
echo "=================================="