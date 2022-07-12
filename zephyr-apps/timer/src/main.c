/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/zephyr.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(timer, LOG_LEVEL_INF);

/* timer expiry function */
void log_time(struct k_timer *timer_id)
{
	unsigned period, uptime;
	period = k_ticks_to_ms_ceil32(timer_id->period.ticks);
	uptime = k_uptime_get();
	LOG_INF("timer(period=%dms): %d", period, uptime);
}

/* timer definition(s) */
K_TIMER_DEFINE(time_logging_4s_timer, log_time, NULL);
K_TIMER_DEFINE(time_logging_2s_timer, log_time, NULL);

void main(void)
{
	// announce app starts
	LOG_INF("timer app started");

	// start timers
	k_timer_start(&time_logging_4s_timer, K_SECONDS(1), K_SECONDS(4));
	k_timer_start(&time_logging_2s_timer, K_SECONDS(1), K_SECONDS(2));
}
