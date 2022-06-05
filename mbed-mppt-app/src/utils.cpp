#include "../include/utils.h"

TimeDelta::TimeDelta(LowPowerTimer *timer){

    // Set reference to the timer object
    timer_ref = timer; 
    prev_time_us = (*timer_ref).elapsed_time();
    curr_time_us = prev_time_us;     
}

float TimeDelta::get_delta_us(){

    curr_time_us = (*timer_ref).elapsed_time();

    // Casting down from long long to float since time span measurements should be very short
    float time_delta = duration_cast<std::chrono::milliseconds>(curr_time_us).count() - duration_cast<std::chrono::milliseconds>(prev_time_us).count();
    prev_time_us = curr_time_us;
    measured_delta = time_delta;

     printf("TimeDelta:get_delta_us: t_delta: %g \n", time_delta);
    
    return time_delta;
}