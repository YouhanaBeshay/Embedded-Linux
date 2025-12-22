# C++ Multiple inheritance task:
- A C++ application for **Raspberry Pi 3b+** that demonstrates:
    - Multiple inheritance (diamond shape)
    - Polymorphism
    - Stream abstraction
    - Hardware interaction (7-segment display)
- The system supports output redirection either to:
    - The terminal
    - A 7-segment display 
 <br>
(<small>*based on the constructed object, while input is always read from the terminal.*</small>)

## Notable Steps on dev machine:
1. Used a *toolchain cmake* file to use our crosscompiler
2. Used  ```set(CMAKE_BUILD_RPATH "$ORIGIN/lib")``` in the main
   - To add a Relative path to the shared libraries (as by defualt cmake add the absolute path only)
   - So that absolute path will be invalid once we run the app on the Pi
   - that saves as from the step of adding the path of the lib to `LD_LIBRARY_PATH` 
<br>
    <small>(Not sure if that was the best solution)</small>

### Steps:
#### on the dev machine:
1. Run cmake using the toolchain file: 
   - ```cmake -S . -B build_pi --toolchain toolchain/toolchain-rpi3.cmake```
2. Build:
   - ```cmake --build build_pi/```
3. Send the folder to the Pi using rsync

#### on Pi:
1. Connect the hardware pins of the 7-segments

    | Segment | GPIO pin |
    | ------- | -------- |
    | A       | GPIO_26  |
    | B       | GPIO_19  |
    | C       | GPIO_13  |
    | D       | GPIO_6   |
    | E       | GPIO_5   |
    | F       | GPIO_0   |
    | G       | GPIO_11  |

2. inside the build directory run the app
   - ```./inheritanceApp ```

# Demo vid:


https://github.com/user-attachments/assets/560e73f8-ff99-40e5-b709-68db05144ea6


