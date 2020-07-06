/*
 * Copyright (c) 2020 Workaround GMBH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/spi.h>

static const struct spi_config spi_cfg = {
	.operation = SPI_WORD_SET(8) | SPI_TRANSFER_MSB |
		     SPI_MODE_CPOL | SPI_MODE_CPHA,
	.frequency = 16000000,
	.slave = 0,
};

struct device * spi_dev;

static void spi_init(void)
{
	spi_dev = device_get_binding(DT_LABEL(DT_ALIAS(spi_4)));
	if (spi_dev == NULL) {
		printk("Could not find SPI driver!\n");
		return;
	}
}

void spi_test_send(void)
{
	int err;
	static u8_t tx_buffer[1];
	static u8_t rx_buffer[1];

	const struct spi_buf tx_buf = {
		.buf = tx_buffer,
		.len = sizeof(tx_buffer)
	};
	const struct spi_buf_set tx = {
		.buffers = &tx_buf,
		.count = 1
	};

	struct spi_buf rx_buf = {
		.buf = rx_buffer,
		.len = sizeof(rx_buffer),
	};
	const struct spi_buf_set rx = {
		.buffers = &rx_buf,
		.count = 1
	};

	err = spi_transceive(spi_dev, &spi_cfg, &tx, &rx);
	if (err) {
		printk("SPI error: %d\n", err);
	} else {
		/* Connect MISO to MOSI for loopback */
		printk("TX sent: %x\n", tx_buffer[0]);
		printk("RX recv: %x\n", rx_buffer[0]);
		tx_buffer[0]++;
	}
}

void main(void)
{
	printk("SPIM Example\n");
	spi_init();

	while (1) {
		spi_test_send();
		k_sleep(K_MSEC(1000));
	}
}
