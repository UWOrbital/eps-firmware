#include "mbed.h"
#include <chrono>

using namespace std::chrono;

class TimeDelta {
    
    private:

        LowPowerTimer *timer_ref;
        microseconds prev_time_us; 
        microseconds curr_time_us; 
        float measured_delta;

    public:

        TimeDelta(LowPowerTimer *timer);

        float get_delta_us();

};