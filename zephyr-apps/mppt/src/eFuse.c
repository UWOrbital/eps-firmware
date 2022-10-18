#include "eFuse.h"
LOG_MODULE_REGISTER(eFuse, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

const struct gpio_dt_spec sig0 = GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), signal_gpios);
//pins c14, c13

//Read E-Fuse pins
int get_efuse_voltage(void)
{
    int ret; 
    int current_state;

    if (!device_is_ready(sig0.port)) {
		return NULL;
	}

    ret = gpio_pin_configure_dt(&sig0, GPIO_INPUT, GPIO_ACTIVE_HIGH); //how to add two flags 
	if (ret < 0) {
		return NULL;
    }
    
    current_state = gpio_port_get_dt(&sig0);
    LOG_INF("E-fuse current state is {0}\n", current_state);
    return current_state;
}

//Pull E-Fuse pins to ground via open drain
void set_eFuse_low(void)
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

	while (1) {
        
        if(current_state == 0 || current_state == NULL) {
            return;
        }
        else{
            ret = gpio_pin_configure_dt(&sig0, GPIO_OPEN_DRAIN);
            //GPIO_OUTPUT_INACTIVE, GPIO_OUTPUT_LOW ?
            if (ret < 0) {
                return;
            }         
        }

		k_msleep(SLEEP_TIME_MS);
		LOG_INF("E-fuse disconnected\n");
	}
}

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

	while (1) {
        
        if(current_state == 0 || current_state == NULL) {
            return;
        }
        else{
            ret = gpio_pin_configure_dt(&sig0, GPIO_OUTPUT, GPIO_OPEN_DRAIN); //cannot drive to any voltage
            
            if (ret < 0) {
                return;
            }         
        }

		k_msleep(SLEEP_TIME_MS);
		LOG_INF("E-fuse reconnected\n");
	}
}