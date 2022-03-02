#include "mbed.h"
#include "sensors.h"

enum duty_cycle {DECREASE = 0, INCREASE = 1};

class Mppt {
    
    private:
        float current, voltage;
        float dv, di; 
        int cycle_time_ms;
        Timer timer;  

    public:

        Mppt(float current, float voltage, int cycle_ms);

        void set_voltage(float voltage);

        void set_current(float current);

        int calc_mppt();

        void run_mppt();

    private:

        void calc_dv(){
            
        }

        void calc_di(){

        }

};