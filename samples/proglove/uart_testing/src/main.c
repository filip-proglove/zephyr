/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/uart.h>
#include <string.h>

/*
 * If you want to test this sample in the IRQ driven mode
 * go to the prj.conf file and set CONFIG_UART_INTERRUPT_DRIVEN=y
 *
 * Note:
 * printk(); console uses UART_0 for sending data
 */

const char *test_string = "Proba123Ovo je neki dugacak string za testiranje\n\r"
		"Sada ide drugi red987654321ende\n\r\0";

unsigned char recv_buffer[200];
volatile unsigned char recv_char;

static volatile bool data_received;
static volatile int len_received;

static void uart_write_blocking(struct device *uart_dev,
		unsigned char *data, unsigned int len) {

	for (int i=0; i<len; i++) {
		uart_poll_out(uart_dev, data[i]);
	}
}

#if defined(CONFIG_UART_INTERRUPT_DRIVEN)
static void my_uart_cb(struct device *dev) {

	uint8_t recvData;

	if (!uart_irq_update(dev)) {
		return;
	}

	if (uart_irq_rx_ready(dev)) {
		uart_fifo_read(dev, &recvData, 1);

		recv_buffer[len_received++] = recvData;

		if ((recvData == '\n') || (recvData == '\r')) {
			/* Full message received, we got termination chars */
			recv_buffer[len_received++] = '\n';
			recv_buffer[len_received++] = '\r';
			data_received = true;
		}
	}
}
#endif


static void uart_echo_test(struct device *uart_dev) {

	k_timeout_t sleep_ms;
	sleep_ms = K_MSEC(10);

	while (1) {
#if defined(CONFIG_UART_INTERRUPT_DRIVEN)
		/* Data has been received in IRQ mode */
		if (data_received) {
			data_received = false;
			uart_write_blocking(uart_dev, recv_buffer, len_received);
			len_received = 0;
		}

#else
		/* Polling mode */
		if (uart_poll_in(uart_dev, (unsigned char *)&recv_char) == 0) {
			if (recv_char == '\n' || recv_char == '\r') {
				uart_poll_out(uart_dev, '\n');
				uart_poll_out(uart_dev, '\r');
			} else {
				uart_poll_out(uart_dev, recv_char);
			}
		}
#endif
		k_sleep(sleep_ms);
	}
}

void main(void)
{
	printk("Uart testing sample!\n");

	struct device *uart_dev;
	uart_dev = device_get_binding(DT_LABEL(DT_ALIAS(uart_1)));
	if (!uart_dev) {
		printk("Could not find UART driver\n");
		goto Exit;
	}

	printk("Testing start!\n");

	uart_write_blocking(uart_dev,
				(unsigned char *)test_string,
				strlen(test_string));
#if defined(CONFIG_UART_INTERRUPT_DRIVEN)
	/* For IRQ driven UART */
	uart_irq_callback_set(uart_dev, my_uart_cb);

	/* Enable Tx/Rx interrupt before using fifo */
	uart_irq_rx_enable(uart_dev);
#endif

	uart_echo_test(uart_dev);

Exit:
	printk("Testing end!\n");
	while (1) {

	}
}
