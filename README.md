# co2nano
Arduino sketch for a Arduino Nano with MH-Z19B CO2 sensor and SSD1306 i2c OLED display

## Used Libraries

- [MH-Z19](https://github.com/WifWaf/MH-Z19) from Jonathan Dempsey
- [NeoSWSerial](https://github.com/SlashDevin/NeoSWSerial) from SlashDevin
- [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306) by Adafruit

## Used Hardware
- Arduino Nano [Documentation](https://store.arduino.cc/arduino-nano) and [Pinout](https://content.arduino.cc/assets/Pinout-NANO_latest.pdf)
- MH-Z19B [Datasheet](https://www.winsen-sensor.com/d/files/MH-Z19B.pdf) 
- DSD Tech SH-S091 (SSD 1306 compatible)


## Circuit

```
     MH-Z19B             Arduino NANO            SSD1306

      Tx     O--------------O D2  
      Rx     O--------------O D3

      GND    O--------------O GND O---------------O GND
      Vin    O--------------0 +5V O---------------O VCC

                              A5  O---------------O SCL
                              A4  O---------------O SDA
```
