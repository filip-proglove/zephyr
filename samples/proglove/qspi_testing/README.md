# Sample app for testing QSPI peripheral on nrf5340-PDK

Sample app that is used to verify QSPI interface.

`nrf5340-PDK` has onboard external Serial NOR Flash memory [MX25R6435F](https://www.macronix.com/Lists/Datasheet/Attachments/7428/MX25R6435F,%20Wide%20Range,%2064Mb,%20v1.4.pdf) with 64Mb bits (8M bytes) of memory.

Since zephyr don’t have support for QSPI for nrf5340 we had to provide our own support by making necessary changes to .dts files.

For changes check out: 
* [soc/arm/nordic_nrf/nrf53/Kconfig.soc](../../../soc/arm/nordic_nrf/nrf53/Kconfig.soc)
* [dts/arm/nordic/nrf5340_cpuapp_common.dtsi](../../../dts/arm/nordic/nrf5340_cpuapp_common.dtsi)

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
