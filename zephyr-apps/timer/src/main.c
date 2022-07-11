/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/zephyr.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

#define SW0_NODE DT_ALIAS(sw0)

static const struct gpio_dt_spec sw = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

void main(void)
{
	int ret;
	int rising_edge = 1;
	LOG_INF("timer started\n");

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
			LOG_INF("milliseconds since boot: %lld\n", k_uptime_get());
		}
	}
}
