#include <zephyr/zephyr.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

// Find devicetree configurations
#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), signal_gpios)
#error "No suitable devicetree overlay specified"
#endif

int get_efuse_voltage();

void set_eFuse_low(); 
void set_eFuse_high();

