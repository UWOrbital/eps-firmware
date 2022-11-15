#include "eFuse.h"
LOG_MODULE_REGISTER(mppt_eFuse, LOG_LEVEL_INF);

//Defaults pin c14 to active at high voltage
const struct gpio_dt_spec sig0 = GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), signal_gpios);

//Read E-Fuse pins
int get_efuse_voltage(void)
{
    int ret; 
    int current_state;

    if (!device_is_ready(sig0.port)) {
		return -1;
	}

    ret = gpio_pin_configure_dt(&sig0, GPIO_OUTPUT);
	if (ret < 0) {
		return -1;
    }
    
    current_state = gpio_pin_get_dt(&sig0);
    if (current_state < 0) {
        return -1;
    }
    
    LOG_INF("E-fuse current state is (%i)\n", current_state);
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
        
    if(current_state != 1) {
        LOG_INF("E-fuse pin is already disabled\n");
        return;
    }
    else
    {
        ret = gpio_pin_configure_dt(&sig0, GPIO_OPEN_DRAIN);
        if (ret < 0) {
            return;
        }    
    }
    
    current_state = get_efuse_voltage();
    if(current_state != 0) return;

    LOG_INF("E-fuse had been disabled\n");
	
}

//Pull E-Fuse pins high
void set_eFuse_high()
{
    int ret;
    int current_state = get_efuse_voltage();

	if (!device_is_ready(sig0.port)) {
		return;
	}

    if(current_state != 0) {
        LOG_INF("E-fuse pin is already enabled\n");
        return;
    }
    else
    {
        ret = gpio_pin_configure_dt(&sig0, GPIO_OUTPUT_HIGH);
        if (ret < 0) {
            return;
        } 
    }
    
    current_state = get_efuse_voltage();
    if(current_state != 1) return;
    
    LOG_INF("E-fuse had been enabled\n");
}