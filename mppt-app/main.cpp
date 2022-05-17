#include "mbed.h"
#include <chrono>
#include <cstdint>
#include <cstdio>

using namespace std::chrono;

#define BLINKING_RATE     5000ms
#define SAMPLE_RATE       50ms
#define PWM_RATE          500ms
#define V_REF             3.3
#define V_OFFSET          2.7641
#define GAIN              1.0
#define V_NOLOAD          4.0

// Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut dout(LED1);
#else
    bool dout;
#endif

// Initialize a pins to perform analog input and digital output functions
AnalogIn ain(PA_0, V_REF);

// Using Low Power timer because it does not block deep sleep mode
LowPowerTimer timer; 

// LED1 is PWM Capable 
PwmOut pwm_led(LED1);
PwmOut pwm_out(PA_1); // PWM Capable pin

// Reference Voltage
float ref_v = V_REF;

// main() runs in its own thread in the OS
int main()
{

    printf("Running Mbed OS %d\n", MBED_MAJOR_VERSION);
    printf("Initial ADC Vref %f\n", ain.get_reference_voltage());
 
    // Set reference voltage
    ain.set_reference_voltage(5.0);
    ref_v = ain.get_reference_voltage();

    printf("ADC Vref %f\n", ref_v);
    float raw = 0; 

    // Store timer reads
    // Using microseconds std::chrono types 
    microseconds time_delta; 

    // Start timer
    timer.start(); 

    // PWM Control
    pwm_led.period(4.0f);      // 4 second period

    while (true) {

        printf("\n Next ==> \n");

        // Sleep for defined time
        ThisThread::sleep_for(BLINKING_RATE);

        // print the percentage and 16 bit normalized values
        raw = ain.read();
        printf("raw: %g \n", raw);
        printf("voltage: %g \n", (raw*ref_v));
        printf("current: %g \n", (raw*ref_v) - V_NOLOAD);

        // Read timer values 
        time_delta = timer.elapsed_time();
        printf("Elapsed time: %llu milliseconds\n", duration_cast<std::chrono::milliseconds>(time_delta).count());

        // Vary the duty cycle from 0 to 95%
        for(float duty = 0.0; duty < 1.0; duty += 0.05){
            pwm_led.write(duty);
            // printf("Writing PWM: %g \n", duty);
            ThisThread::sleep_for(PWM_RATE);
        }

    }
}

