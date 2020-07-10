# Sample app for testing UART peripherals on nrf5340-PDK

Sample app that is used to verify UART interface. This sample uses `UART_1` instance.

In order to use sample in polling mode just build and flash binary without any changes.

For IRQ based handling go to the `prj.conf` and set `CONFIG_UART_INTERRUPT_DRIVEN=y`.

## Prerequisites

Pins used:
* Tx pin - P0.04
* Rx pin - P0.05

Baud rate is `115200`.

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

Note: The console logging output uses `UART_0` peripheral.

To see the logs form the `UART_1` use USB to serial convertor to connect board to PC.

Use putty to check functionality by connecting to `/dev/ttyUSB0` with `115200` baud rate.

Echo sample is running, what you type will be echoed back to you.
