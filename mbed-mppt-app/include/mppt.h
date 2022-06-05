#include "mbed.h"
#include "utils.h"
#include "acs723.h"

enum duty_cycle {DECREASE = 0, INCREASE = 1}; 

class Mppt {
    
    private:

        float v0, v1, i0, i1, t_delta; 
        float dv, di; 
        LowPowerTimer timer;

        // ADC connected to voltage sensor
        AnalogIn *analog_in;

        // GPIO connected to digital potentiometer
        PwmOut *pwm_out; 

        void set_voltage();

        void set_current();

        int calc_mppt(float t_delta);

    public:

        Mppt(AnalogIn *a_in, PwmOut *pwm_o);

        void run_mppt();

};