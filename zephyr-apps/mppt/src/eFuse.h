//#include <zephyr/zephyr.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

// Find devicetree configurations
#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), signal_gpios)
#error "No suitable devicetree overlay specified"
#endif

#define SUCCESS 1

int8_t efuse_init(void);

int8_t get_efuse_voltage(void);

int8_t set_eFuse_low(void); 

int8_t set_eFuse_high(void);
