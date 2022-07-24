#include <zephyr/logging/log.h>

#include "adc.h"

LOG_MODULE_REGISTER(mppt_adc, LOG_LEVEL_INF);

/* Data of ADC io-channels specified in devicetree. */
static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
			     DT_SPEC_AND_COMMA)
};

/* Labels of ADC controllers referenced by the above io-channels. */
static const char *const adc_labels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
			     LABEL_AND_COMMA)
};

static int16_t sample_buffer[1];
static struct adc_sequence sequence = {
	.buffer      = sample_buffer,
	
	/* buffer size in bytes, not number of samples */
	.buffer_size = sizeof(sample_buffer),
};
static uint16_t vref_mv[ARRAY_SIZE(adc_channels)] = { 0 };

// Configure ADC device struct
static void configure_channel(const struct adc_dt_spec *dt_spec,
			      uint16_t *vref_mv)
{
	/* If a configuration for the channel is specified in devicetree,
	 * use it, otherwise use default settings that should be suitable
	 * for most ADCs.
	 */
	if (dt_spec->channel_cfg_dt_node_exists) {
		adc_channel_setup(dt_spec->dev, &dt_spec->channel_cfg);

		/* For the internal reference, use the voltage value returned
		 * by the dedicated API function. For others, use the value
		 * from devicetree if available.
		 */
		if (dt_spec->channel_cfg.reference == ADC_REF_INTERNAL) {
			*vref_mv = adc_ref_internal(dt_spec->dev);
		} else if (dt_spec->vref_mv > 0) {
			*vref_mv = dt_spec->vref_mv;
		}
	} else {
		struct adc_channel_cfg channel_cfg = {
			.channel_id       = dt_spec->channel_id,
			.gain             = ADC_GAIN,
			.reference        = ADC_REFERENCE,
			.acquisition_time = ADC_ACQUISITION_TIME,
		};

		adc_channel_setup(dt_spec->dev, &channel_cfg);

		*vref_mv = adc_ref_internal(dt_spec->dev);
	}
}

static void prepare_sequence(struct adc_sequence *sequence,
			     const struct adc_dt_spec *dt_spec)
{
	sequence->channels     = BIT(dt_spec->channel_id);
	sequence->resolution   = ADC_RESOLUTION;
	sequence->oversampling = 0;

	if (dt_spec->channel_cfg_dt_node_exists) {
		if (dt_spec->resolution) {
			sequence->resolution = dt_spec->resolution;
		}
		if (dt_spec->oversampling) {
			sequence->oversampling = dt_spec->oversampling;
		}
	}
}

static void print_millivolts(int32_t value,
			     uint16_t vref_mv,
			     uint8_t resolution,
			     const struct adc_dt_spec *dt_spec)
{
	enum adc_gain gain = ADC_GAIN;

	if (dt_spec->channel_cfg_dt_node_exists) {
		gain = dt_spec->channel_cfg.gain;

		/*
		 * For differential channels, one bit less needs to be specified
		 * for resolution to achieve correct conversion.
		 */
		if (dt_spec->channel_cfg.differential) {
			resolution -= 1;
		}
	}

	adc_raw_to_millivolts(vref_mv, gain, resolution, &value);
	LOG_INF(" = %d mV", value);
}

void setup_adc(){
	
	/* Configure channels individually prior to sampling. */
	for (uint8_t i = 0; i < ARRAY_SIZE(adc_channels); i++) {
		if (!device_is_ready(adc_channels[i].dev)) {
			LOG_INF("ADC device not found\n");
			return;
		}

		configure_channel(&adc_channels[i], &vref_mv[i]);
	}

}

void poll_adc_channels(){

	int err;
	
	for (uint8_t i = 0; i < ARRAY_SIZE(adc_channels); i++) {
		LOG_INF("- %s, channel %d: ", adc_labels[i], adc_channels[i].channel_id);

		prepare_sequence(&sequence, &adc_channels[i]);

		err = adc_read(adc_channels[i].dev, &sequence);
		if (err < 0) {
			LOG_INF("error %d\n", err);
			continue;
		} else {
			LOG_INF("%d", sample_buffer[0]);
		}

		/*
		* Convert raw reading to millivolts if the reference
		* voltage is known.
		*/
		if (vref_mv[i] > 0) {
			print_millivolts(sample_buffer[0],
			vref_mv[i],
			sequence.resolution,
			&adc_channels[i]);
		}
	}
}

