#include "../include/mppt.h"
#include <cstdint>

#define SLEEP_CYCLE_MS 1000ms

// ====================== Helper Methods ======================

float calc_dv(float t0, float t1, float v0, float v1){
    
    return (v1 - v0)/(t1 - t0);
}

float calc_di(float t0, float t1, float i0, float i1){

    return (i1 - i0)/(t1 - t0);
}

// ====================== Class Implementation ======================

Mppt::Mppt(float current, float voltage){
    current = current;
    voltage = voltage;

    // Seed initial values
    v0 = voltage; 
    i0 = current;     
}

void Mppt::set_current(float current){
    current = current;
}

void Mppt::set_voltage(float voltage){
    voltage = voltage;
}

/*
Main loop for running MPPT
*/
void Mppt::run_mppt(){

    // Start timer to track time 
    timer.start();

    // Initialize values
    // t0 = duration_cast<std::chrono::milliseconds>(t.elapsed_time()).count(); // get time
    
    while(true){

        printf("Running MPPT");

        // Main steps 
        /*
        1. Get current and voltage values 
        2. Calculate MPPT
        3. Change power output (duty cycle)
        */

        // Sleep for a certain amount of time
        ThisThread::sleep_for(SLEEP_CYCLE_MS);

    }
}

int Mppt::calc_mppt(){
    //  float di = calc_di();
    //  float dv = calc_dv();

     if (dv == 0){

         if (di == 0){
             return INCREASE;
         } else {

             if (di > 0){
                 return INCREASE;
             } else {
                 return DECREASE;
             }
         }

     } else {

         float di_dv = di / dv; 
         float i_v = current / voltage; 

         if (di_dv == i_v){
             return INCREASE;
         } else {
             
             if (di_dv > -i_v){
                 
                 if (dv > 0){
                     return INCREASE;
                 } else {
                     return DECREASE;
                 }
             } else {
                 return DECREASE;
             }
         }

     }
}