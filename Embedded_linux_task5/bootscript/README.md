# Boot script for intializing the u-boot environment

## How to compile :

### for raspberry pi 3b+
```bash
/home/youhana/ITI_assignments2/Embedded_linux_libs/u_boot/u-boot-2026.01-rc5/tools/mkimage -A arm64 -T script -C none -n "Boot script" -d custombootscript.cmd myboot.scr
```
### for vexpress
```bash
/home/youhana/ITI_assignments2/Embedded_linux_libs/u_boot/u-boot-2026.01-rc5/tools/mkimage -A arm -T script -C none -n "Boot script" -d vexpressbootscript.cmd vexboot.scr
```

---
## send to tftp server:

### for raspberry pi 3b+
```bash
sudo cp myboot.scr /srv/tftp
```
### for vexpress
```bash
sudo cp vexboot.scr /srv/tftp
```
