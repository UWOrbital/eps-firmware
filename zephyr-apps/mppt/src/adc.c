#include <zephyr/logging/log.h>

#include "adc.h"

LOG_MODULE_REGISTER(mppt_adc, LOG_LEVEL_INF);

// For current sensor readings
#define CURRENT_SENSOR_GAIN -1.5 

// In mV
#define REFERENCE_VOLTAGE 2550 

/* Data of ADC io-channels specified in devicetree. */
static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
			     DT_SPEC_AND_COMMA)
};

static int16_t buf;
static struct adc_sequence sequence = {
	.buffer      = &buf,
	/* buffer size in bytes, not number of samples */
	.buffer_size = sizeof(buf),
};

int8_t setup_adc(){

	int8_t err = 0;
	
	/* Configure channels individually prior to sampling. */
	for (uint8_t i = 0; i < ARRAY_SIZE(adc_channels); i++) {
		if (!device_is_ready(adc_channels[i].dev)) {
			LOG_ERR("ADC device not found \n");
			return -ENODEV;
		}

		err = adc_channel_setup_dt(&adc_channels[i]);
		if (err < 0) {
			printk("Could not setup channel #%d (%d)\n", i, err);
			return -ENODEV;
		}
		LOG_INF("ADC(%s), channel [%d]: Configured", adc_channels[i].dev->name, adc_channels[i].channel_id);
	}

	return err;
}

void read_adc_channels(){

	int err; 
	int32_t val_mv;
	
	for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {

		LOG_INF("- %s, channel %d: ",
				adc_channels[i].dev->name,
				adc_channels[i].channel_id);

		(void)adc_sequence_init_dt(&adc_channels[i], &sequence);

		err = adc_read(adc_channels[i].dev, &sequence);
		if (err < 0) {
			LOG_INF("Could not read (%d)\n", err);
			continue;
		} else {
			LOG_INF("%"PRId16, buf);
		}

		/* conversion to mV may not be supported, skip if not */
		val_mv = buf;
		err = adc_raw_to_millivolts_dt(&adc_channels[i],
							&val_mv);
		if (err < 0) {
			LOG_INF(" (value in mV not available)\n");
		} else {
			LOG_INF(" = %"PRId32" mV\n", val_mv);
		}
	}
}

int32_t read_adc_channel(int8_t chn){

	int err; 
	int32_t val_mv;
	
	(void)adc_sequence_init_dt(&adc_channels[chn], &sequence);

	err = adc_read(adc_channels[chn].dev, &sequence);
	if (err < 0) {
		LOG_INF("Could not read (%d)\n", err);
	} 

	/* conversion to mV may not be supported, skip if not */
	val_mv = buf;
	err = adc_raw_to_millivolts_dt(&adc_channels[chn], &val_mv);
	if (err < 0) {
		LOG_INF(" (value in mV not available)\n");
	} 	

	return val_mv;
}

float get_current_reading(int8_t num_samples){
	
	int8_t channel_num = 0; 
	int32_t avgVal_mV = 0; 

	for (int8_t i = 0; i < num_samples; i++){
		
		// Get reading in mV
		avgVal_mV += read_adc_channel(channel_num); 
	}

	// Get readings average
	avgVal_mV = avgVal_mV / num_samples; 
	
	LOG_INF("Current Reading(mV) = %"PRId32" mV\n", avgVal_mV);

	// Perform conversion
	float current = (avgVal_mV - REFERENCE_VOLTAGE)*CURRENT_SENSOR_GAIN;

	LOG_INF("Current = %"PRId32" mA", (int32_t)current);

	return current; 

}
