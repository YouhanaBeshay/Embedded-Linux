# Raspberry Pi 3B+ C++ GPIO Driver

## Steps

### On Dev Machine

1. **Cross compile the library source file to object files**
   ```bash
   aarch64-rpi3-linux-gnu-g++ -c *.cpp -o mygpio.o
   ```

2. **Create dynamic library from those object files**
   ```bash
   aarch64-rpi3-linux-gnu-g++ -shared -fPIC *.o -o libmygpio.so
   ```

3. **Move to `/src` and compile the `main.cpp`**
   ```bash
   cd ../src/
   aarch64-rpi3-linux-gnu-g++ main.cpp -lmygpio -L../lib -I../lib -o main.out
   ```

4. **Send over the files to the Pi using `rsync`**
   ```bash
   rsync -avz Embedded_linux_task2 pi@pi_ip_address:/home/pi/some_directory
   ```

### On the Pi

1. **Add `LD_LIBRARY_PATH` environment variable**
   ```bash
   export LD_LIBRARY_PATH=/home/pi/some_directory/Embedded_linux_task2/lib/
   ```

2. **Move inside the `/src` and run the output file**
   ```bash
   cd /home/pi/some_directory/Embedded_linux_task2/src
   ./main.out
   ```