#include "mbed.h"
#include "sensors.h"

class Mppt {
    
    private:
        float current, voltage;
        float dv, di;  

    public:

        Mppt(float current, float voltage);

        void set_voltage(float voltage);

        void set_current(float current);

        void run_mppt();

    private:

        void calc_dv();

        void calc_di();

};