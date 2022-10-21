#include "eFuse.h"
LOG_MODULE_REGISTER(eFuse, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

//Defaults pin c14 to active at high voltage
const struct gpio_dt_spec sig0 = GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), signal_gpios);

//Read E-Fuse pins
int get_efuse_voltage(void)
{
    int ret; 
    int current_state;

    if (!device_is_ready(sig0.port)) {
		return NULL;
	}

    ret = gpio_pin_configure_dt(&sig0, GPIO_INPUT);
	if (ret < 0) {
		return NULL;
    }
    
    current_state = gpio_port_get(&sig0);
    LOG_INF("E-fuse current state is {0}\n", current_state);
    return current_state;
}

//Pull E-Fuse pins to ground via open drain
void set_eFuse_low()
{
	int ret;
    int current_state = get_efuse_voltage();

	if (!device_is_ready(sig0.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&sig0, GPIO_OUTPUT);
	if (ret < 0) {
		return;
	}
        
    if(current_state == 0 || current_state == NULL) {
        return;
    }
    else
    {
        ret = gpio_pin_configure_dt(&sig0, GPIO_OPEN_DRAIN);
        if (ret < 0) {
            return;
        }    
    }

    LOG_INF("E-fuse is in Open Drain mode\n");
	
}

//Take E-Fuse pins off open drain mode
void set_eFuse_high();
{
    int ret;
    int current_state = get_efuse_voltage();

	if (!device_is_ready(sig0.port)) {
		return;
	}

	ret = gpio_pin_configure_dt(&sig0, GPIO_OUTPUT);
	if (ret < 0) {
		return;
	}
    
    LOG_INF("E-fuse is not in Open Drain mode\n");
}