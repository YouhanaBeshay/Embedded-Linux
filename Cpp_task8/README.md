# vSomeIP CapsLock Subscribe and Notify :

- A vsomeip-based application where a **PC service** monitors CapsLock LED state and broadcasts it to a **Raspberry Pi 3 client** over Ethernet using SOME/IP protocol.

---

## Build Steps

### On the PC

1. **Cross-compile Boost** for aarch64 using `user-config.jam`
2. **Cross-compile vsomeip** for aarch64 using the toolchain file
- *for more details on the first 2 steps [Click here](Cross_compile.md)*
1. **Compile the service** normally (native build)
2. **Compile the client** using `rpi3-toolchain.cmake` (points to cross-compiled libs)

### Deploy to RPi

5. **rsync** the client executable and config to the Pi
6. Create `lib/` directory inside the build folder
7. Copy cross-compiled Boost and vsomeip `.so` files into `lib/`

> This works because CMake uses `set(CMAKE_BUILD_RPATH "$ORIGIN/lib")`
- <small>(This is instead of using LD_LIBRARY_PATH)</small>

---

## Running

### On PC (Service)
nside the build directory:
```bash
sudo route add -nv 224.224.224.245 dev eth0
export VSOMEIP_CONFIGURATION=../vsomeip_server.json
sudo -E ./vsomeip_server
```

### On RPi (Client)
Inside the build directory:
```bash
sudo route add -nv 224.224.224.245 dev eth0
export VSOMEIP_CONFIGURATION=../vsomeip_client.json
./vsomeip_client
```


