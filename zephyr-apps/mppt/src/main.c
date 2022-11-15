#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include "adc.h"
#include "eFuse.h"

LOG_MODULE_REGISTER(mppt, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   2500

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
Initialize GPIO LED
*/
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void main(void)
{
	int ret;

	if (!device_is_ready(led.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}

	// ret = setup_adc();
	// if (ret < 0) {
	// 	return;
	// }

	// toggle for testing
	uint8_t toggle = 0; 
	int gpio_state = 0;

	while (1) {

		LOG_INF("Running Main(%"PRId32")...", toggle);

		if (toggle == 1) {
			LOG_INF("set_eFuse_high()");
			set_eFuse_high();
		} else{
			LOG_INF("set_eFuse_low()");
			set_eFuse_low();
		}

		// read gpio pin c14 
		gpio_state = get_efuse_voltage();
		LOG_INF("gpio = %"PRId32" state\n", gpio_state);
		
		//read_adc_channels();

		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return;
		}
		
		k_msleep(SLEEP_TIME_MS);
		toggle ^= 1; // flip toggle bit

	}
}
