# STM32 → Raspberry Pi UART Logging

## Overview
- In this task we send ADC values from an STM32 microcontroller to a Raspberry Pi 3B+ over UART. 
- The Raspberry Pi reads and logs the incoming data.

---

## STM32 Configuration
1. Configure the STM32 ADC to read the desired analog input.
2. Transmit ADC readings through UART at a fixed baud rate.

---

## Hardware Connection
Used  **USB-TTL** as i had issues directly connected the UART the Pi.


The TTL appears as `/dev/ttyUSB0`.

---

## Raspberry Pi Setup

### 1. Configure Serial Port
Run:
```bash
sudo raspi-config
