#include "../include/mppt.h"

Mppt::Mppt(float current, float voltage, int cycle_ms){
    current = current;
    voltage = voltage;
    cycle_time_ms = cycle_ms;
}

void Mppt::set_current(float current){
    current = current;
}

void Mppt::set_voltage(float voltage){
    voltage = voltage;
}

void Mppt::run_mppt(){

    // Start timer to track time 
    timer.start();
     
    while(true){

    }
}

int Mppt::calc_mppt(){
     calc_di();
     calc_dv();

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