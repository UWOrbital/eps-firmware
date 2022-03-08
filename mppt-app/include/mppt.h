#include "mbed.h"
#include "sensors.h"

enum duty_cycle {DECREASE = 0, INCREASE = 1};

class Mppt {
    
    private:
        float current, voltage;
        float v0, v1, i0, i1, t0, t1; 
        float dv, di; 
        Timer timer;  

    public:

        Mppt(float current, float voltage);

        void set_voltage(float voltage);

        void set_current(float current);

        int calc_mppt();

        void run_mppt();

};