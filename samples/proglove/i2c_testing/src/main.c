/*
 * Copyright (c) 2015 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/i2c.h>

/**
 * @file Sample app using the DS1307 Tiny RTC board to test I2C.
 *
 * Reference:
 *  - https://www.elecrow.com/wiki/index.php?title=Tiny_RTC
 *  - https://datasheets.maximintegrated.com/en/ds/DS1307.pdf
 *
 *  On the Tiny RTC board remove on board R2 and R3 pull up resistors,
 *  and instead pull up SCL and SDA to 3.3V (VDD on nrf5340) via 5.1K resistors.
 *  This is needed since DS1307 uses 5V, and our nrf5340 uses 3.3V.
 *
 *  DS1307 max I2C speed is 100kHz
 *
 *  nrf5340 I2C can go up to 400kHz (Fast Speed Mode)
 */

#define I2C_DEV DT_LABEL(DT_ALIAS(i2c_1))

/* The I2C address of Tiny RTC */
#define TINY_RTC_I2C_ADDR 0x68

void main(void)
{
	struct device *i2c_dev;
	int ret;

	i2c_dev = device_get_binding(I2C_DEV);
	if (!i2c_dev) {
		printk("I2C: Device driver not found.\n");
		return;
	}

	ret = i2c_reg_write_byte(i2c_dev, TINY_RTC_I2C_ADDR, 0x00, 0x00);
	ret = i2c_reg_write_byte(i2c_dev, TINY_RTC_I2C_ADDR, 0x01, 0x00);
	if (ret) {
		printk("Error reading error code (%d)\n", ret);
		return;
	} else {
		printk("Success writing\n");
	}

	unsigned char seconds = 0;
	unsigned char minutes = 0;

	while (1) {
		ret = i2c_reg_read_byte(i2c_dev, TINY_RTC_I2C_ADDR, 0x00, &seconds);
		ret = i2c_reg_read_byte(i2c_dev, TINY_RTC_I2C_ADDR, 0x01, &minutes);
		if (ret) {
			printk("Error reading error code (%d)\n", ret);
			return;
		} else {
			printk("Time: %d:%d\n", minutes, seconds);
		}
		k_sleep(K_MSEC(1000));
	}
}
