#include "../include/acs723.h"

float measure_voltage(AnalogIn ain){
    
    float ref_v = ain.get_reference_voltage();
    printf("measure_voltage: ADC Vref %f\n", ref_v);

    if (ref_v < REF_V){
        printf("measure_voltage: WARNING: V_REF CONFIG %f\n", ref_v);
    } 

    float avrg_v = 0; 
    for(int i = 0; i < NUM_ADC_SAMPLES; i++ ){
        avrg_v += ain.read();
    }

    avrg_v = avrg_v / NUM_ADC_SAMPLES; 
    float voltage = avrg_v*ref_v;
    printf("measure_voltage: voltage: %g \n", (voltage));

    return voltage;

}

float measure_currrent(AnalogIn ain){

    float voltage = measure_voltage(ain);
    float current = voltage - NO_LOAD_V; 
    printf("measure_currrent: current: %g \n", current);

    return current;
}
