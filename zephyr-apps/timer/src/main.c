#include <zephyr/zephyr.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

void main(void)
{
	int time = 0; 
	while (1) {
		k_msleep(SLEEP_TIME_MS);
		LOG_INF("timer...");

		time = k_uptime_get();
		LOG_INF("time %d", time);
	}
}
