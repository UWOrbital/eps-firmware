/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/zephyr.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

const struct gpio_dt_spec sig0 =
        GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), signal_gpios);

void main(void)
{
	int ret;

	if (!device_is_ready(sig0.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&sig0, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	while (1) {
		ret = gpio_pin_toggle_dt(&sig0);
		if (ret < 0) {
			return;
		}
		k_msleep(SLEEP_TIME_MS);
		LOG_INF("gpio...");
	}
}
