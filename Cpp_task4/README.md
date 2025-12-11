# Raspberry Pi Logging using Smart Pointeres

## Overview
- In this task we send ADC values from an STM32 microcontroller to a Raspberry Pi 3B+ over UART. 
- The Raspberry Pi Displays and logs the incoming data using smart pointers.

---

## STM32 Configuration
1. Configure the STM32 ADC to read the desired analog input.
2. Transmit ADC readings through UART at a fixed baud rate.

- Used arduino framework for fast implementaion
---

## Hardware Connection
Used  **USB-TTL** as i had issues directly connecting the UART pins of the Pi.


The TTL appears as `/dev/ttyUSB0`.

---

## On Raspberry Pi :

### 1. Configure Serial Port
Run:
```bash
sudo raspi-config
```
- Disable serial login shell
- Enable serial hardware port

### 2. Set Baud Rate

- Configure the serial port:
```bash
stty -F /dev/ttyUSB0 115200
```
- (I ran this command inside the constructor of the TempSensor inside the C++ program)


----

## Demo Video:
[Screencast from 12-11-2025 03:40:07 PM.webm](https://github.com/user-attachments/assets/5543aef7-de9a-4eae-a30a-5a38e009570a)
