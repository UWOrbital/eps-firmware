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

/*
* Initialize efuse to a low state. 
*/
int8_t efuse_init(void);

/*
* Read the state of the efuse. 
* Returns -EIO if there is and error.  
*/
int8_t get_efuse_state(void);

/*
* Read the state of the efuse. 
* Returns -EIO if there is and error, otherwise returns the current state.  
*/
int8_t set_eFuse_low(void); 

/*
* Read the state of the efuse. 
* Returns -EIO if there is and error, otherwise returns the current state.  
*/
int8_t set_eFuse_high(void);
