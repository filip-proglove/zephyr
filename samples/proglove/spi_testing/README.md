# Sample app for testing SPI peripherals on nrf5340-PDK

Sample app that is used to verify SPI interface. This sample uses `SPIM_4` (High Speed SPI) instance.

## Prerequisites

Pins used:
* SCK pin - P0.10
* MOSI pin - P0.11
* MISO pin - P0.12

Connect MOSI to MISO directly via jumper wire.

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
