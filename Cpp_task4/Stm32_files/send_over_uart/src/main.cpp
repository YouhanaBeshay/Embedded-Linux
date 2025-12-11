#include <Arduino.h>

HardwareSerial Serial1(PB7, PB6);  // RX, TX for UART1 on Port B

void setup() {
    Serial1.begin(115200);          // UART on PB6/PB7
    analogReadResolution(12);       // 12-bit ADC
}

void loop() {
    // Read ADC from PA0 (LM35)
    uint16_t adcValue = analogRead(PA0);

    // Convert ADC value to millivolts (assuming Vref = 3.3V)
    float voltage_mV = (adcValue * 3300.0) / 4095.0;

    // LM35: 10 mV per °C
    float temperature_C = voltage_mV / 10.0;

    // Send temperature via UART
    Serial1.println(temperature_C);

    // Wait 1 seconds
    delay(1000);
}