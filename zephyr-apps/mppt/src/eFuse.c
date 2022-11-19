#include "eFuse.h"

LOG_MODULE_REGISTER(mppt_efuse, LOG_LEVEL_INF);

//Defaults pin c14 to active at high voltage
const struct gpio_dt_spec sig0 = GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), signal_gpios);

// Initialize e-fuse
int8_t efuse_init(void)
{
    int8_t ret; 

    if (!device_is_ready(sig0.port)) {
		return -EIO;
	}

    // Initialize to be low state
    ret = gpio_pin_configure_dt(&sig0, GPIO_OUTPUT_LOW);
	if (ret < 0) {
		return -EIO;
    }

    return SUCCESS;
}

// Read E-Fuse pins
int8_t get_efuse_state(void)
{
    int8_t ret; 
    int8_t current_state;
    
    current_state = gpio_pin_get_dt(&sig0);
    if (current_state < 0) {
        return -EIO;
    }
    
    LOG_INF("E-fuse current state is (%i)\n", current_state);
    return current_state;
}

//Pull E-Fuse pins to ground via open drain
int8_t set_eFuse_low(void)
{
	int8_t ret;
    int8_t current_state = get_efuse_state();
      
    if(current_state != 1) {
        LOG_INF("E-fuse pin is already disabled\n");
        return SUCCESS;
    }
    else
    {
        ret = gpio_pin_configure_dt(&sig0, GPIO_OUTPUT_LOW);
        if (ret < 0) {
            return -EIO;
        }    
    }
    
    current_state = get_efuse_state();
    if(current_state != 0) return -EIO;

    LOG_INF("E-fuse had been disabled\n");

    return current_state;
	
}

// Pull E-Fuse pins high
int8_t set_eFuse_high()
{
    int8_t ret;
    int8_t current_state = get_efuse_state();

	if (!device_is_ready(sig0.port)) {
		return -EIO;
	}

    if(current_state != 0) {
        LOG_INF("E-fuse pin is already enabled\n");
        return -EIO;
    }
    else
    {
        ret = gpio_pin_configure_dt(&sig0, GPIO_OUTPUT_HIGH);
        if (ret < 0) {
            return -EIO;
        } 
    }
    
    current_state = get_efuse_state();
    if(current_state != 1) return -EIO;
    
    LOG_INF("E-fuse had been enabled\n");

    return current_state;
}