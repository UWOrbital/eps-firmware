#include "mbed.h"

#define REF_V 5.0

// Determined experimentally as the measured voltage from the sesnor when the current is 0A
#define NO_LOAD_V 4.0

// Number of reads to perform of the ADC for each voltage read
// Basic filter used to smooth out the reading through averaging
#define NUM_ADC_SAMPLES 10

float measure_voltage(AnalogIn ain);

float measure_currrent(AnalogIn ain);
