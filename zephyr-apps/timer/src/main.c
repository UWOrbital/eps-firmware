/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/zephyr.h>
#include <zephyr/drivers/gpio.h>
#include <logging/log.h>
#include <zephyr/kernel.h>
LOG_MODULE_REGISTER(main);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
// #define LED0_NODE DT_ALIAS(led0)
#define SW0_NODE DT_ALIAS(sw0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
// static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec sw = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

void main(void)
{
	int ret;
	int rising_edge = 1;
	printk("timer started\n");

	if (!device_is_ready(sw.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&sw, GPIO_INPUT);
	if (ret < 0) {
		return;
	}

	// read time since boot with PA_0 (middle blue joystick) button
	while (1) {
		ret = gpio_pin_get_dt(&sw);
		if (rising_edge == 0 && ret == 0)
		{
			rising_edge = 1;
		}
		else if (rising_edge == 1 && ret == 1)
		{
			rising_edge = 0;
			printk("milliseconds since boot: %lld\n", k_uptime_get());
		}
	}

	// print time since boot every second
	// while (1)
	// {
	// 	printk("milliseconds since boot: %lld\n", k_uptime_get());
	// 	k_msleep(SLEEP_TIME_MS);
	// }
}
