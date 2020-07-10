# Sample apps for testing BLE functionality on nrf5340-PDK

This directory contains two sample apps which we use for testing BLE functionality.
* hci_rpmsg - sample app that should be built and run on network core
* peripheral - sample app that should be built and run on application core

Sample video for utilizing both cores on nRF5340:
* https://www.youtube.com/watch?v=uqKxmsrP2Hc

## Build and flash samples

### Network core binary
Go to the `hci_rpmsg/` directory and execute next commands:
```
mkdir build && cd build
cmake -DBOARD=nrf5340pdk_nrf5340_cpunet ..
make -j4
make flash
```
### Application core binary
Go to the `peripheral/` directory and execute next commands:
```
mkdir build && cd build
cmake -DBOARD=nrf5340pdk_nrf5340_cpuapp ..
make -j4
make flash
```

## Logging
In order to get the log output from the network core connect next pins on the nrf5340 dev kit with jumper wires:
* P0.25 ↔︎ RxD
* P0.26 ↔︎ TxD
* P0.10 ↔︎ CTS
* P0.12 ↔︎ RTS

For monitoring both core log outputs open two terminals and attach each to the following serial ports:

Serial terminal for monitoring application core log output is ttyACM2.
```
sudo minicom --device /dev/ttyACM2
```

Serial terminal for monitoring network core log output is ttyACM1:
```
sudo minicom --device /dev/ttyACM1
```

## Using demo
In order to verify if the demo is functional install `nRF connect` application on your smart phone and use it. 

If you want to use PC instead you'll need external `nrf52840 dongle` and also `nRF connect` on your PC.

nrf5340 dev kit will advertise with name `Zephyr Peripheral Sample Long`.

During connecting and reading GATT attributes check out log outputs on your terminals.
