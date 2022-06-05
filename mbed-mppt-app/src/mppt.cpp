#include "../include/mppt.h"
#include <cstdint>

#define SLEEP_CYCLE_MS 1000ms

// ====================== Helper Methods ======================

float calc_dv(float t_delta, float v0, float v1){
    
    return (v1 - v0)/(t_delta);
}

float calc_di(float t_delta, float i0, float i1){

    return (i1 - i0)/(t_delta);
}

// ====================== Class Implementation ======================

Mppt::Mppt(AnalogIn *a_in, PwmOut *pwm_o){

    // Set peripherals
    analog_in = a_in;
    pwm_out = pwm_o;      
}

void Mppt::set_current(){
    i0 = i1; 
    i1 = measure_currrent(*analog_in);
}

void Mppt::set_voltage(){
    v0 = v1;
    v1 = measure_voltage(*analog_in);
}

/*
Main loop for running MPPT
*/
void Mppt::run_mppt(){

    // Start timer to track time 
    timer.start();

    // Initialize object to track time deltas
    TimeDelta time_delta(&timer);
    float t_delta = 1; 

    // Set pwm period 
    // PWM Control
    (*pwm_out).period(4.0f);
    float duty = 0.5;
    int vary_cycle = 0;

    // Initialize values
    v0 = measure_voltage(*analog_in); 
    i0 = measure_currrent(*analog_in);
    
    while(true){

        printf("Running MPPT");

        // Main steps 
        /*
        1. Get current and voltage values 
        2. Calculate MPPT
        3. Change power output (duty cycle)
        */
        set_current();
        set_voltage();

        t_delta = time_delta.get_delta_us();
        t_delta = t_delta/1000000; // Convert to seconds
        vary_cycle = calc_mppt(t_delta);

        // Determine how to vary the duty cycle
        if (vary_cycle == INCREASE){
            duty += 0.05; 
        } else {
            duty -= 0.05;
        }

        (*pwm_out).write(duty);
        printf("Writing PWM: %g \n", duty);

        // Sleep for a certain amount of time
        ThisThread::sleep_for(SLEEP_CYCLE_MS);

    }
}

int Mppt::calc_mppt(float t_delta){
    
    float di = calc_di(t_delta, i0, i1);
    float dv = calc_dv(t_delta, v0, v1);

     if (dv == 0){

         if (di == 0){
             printf("dv=0 INCREASE");
             return INCREASE;
         } else {

             if (di > 0){
                 printf("dv=0:di>0 INCREASE");
                 return INCREASE;
             } else {
                 printf("dv=0:di<0 DECREASE");
                 return DECREASE;
             }
         }

     } else {

         float di_dv = di / dv; 

         float curr_i = measure_currrent(*analog_in); 
         float curr_v = measure_voltage(*analog_in);

         float i_v = curr_i / curr_v; 

         if (di_dv == i_v){
             printf("dv!=0:di_dv==i_v INCREASE");
             return INCREASE;
         } else {
             
             if (di_dv > -i_v){
                 
                 if (dv > 0){
                     printf("dv!=0:di_dv==i_v:di_dv>-i_v:dv>0 INCREASE");
                     return INCREASE;
                 } else {
                     printf("dv!=0:di_dv==i_v:di_dv>-i_v:dv<0 DECREASE");
                     return DECREASE;
                 }
             } else {
                 printf("dv!=0:di_dv==i_v:di_dv<-i_v DECREASE");
                 return DECREASE;
             }
         }

     }
}