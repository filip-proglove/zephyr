# Sample app for testing I2C peripherals on nrf5340-PDK

Sample app uses the DS1307 Tiny RTC board to test I2C. This sample uses `I2C_1` instance.

Reference for Tiny RTC:
* https://www.elecrow.com/wiki/index.php?title=Tiny_RTC
* https://datasheets.maximintegrated.com/en/ds/DS1307.pdf

## Prerequisites

On the Tiny RTC board remove on board `R2` and `R3` pull up resistors, instead pull up `SCL` and `SDA` to 3.3V (VDD on nrf5340) via 5.1K resistors.
This is needed since DS1307 uses 5V, and our nrf5340 uses 3.3V.

Pins used:
* SDA pin - P1.02 (34)
* SCL pin - P1.03 (35)

## Build and flash sample app

```
mkdir build && cd build
cmake -DBOARD=nrf5340pdk_nrf5340_cpuapp ..
make -j4
make flash
```

## Logging
In order to see log output from the board connect to the `/dev/ttyACM2` serial port:

```
sudo minicom --device /dev/ttyACM2
```