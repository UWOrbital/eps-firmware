#include "mbed.h"
#include <chrono>
#include <cstdint>
#include <cstdio>

using namespace std::chrono;

#define BLINKING_RATE     5000ms
#define SAMPLE_RATE       50ms
#define V_REF             3.3
#define V_OFFSET          2.7641
#define GAIN              1.0

// Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

// Initialize a pins to perform analog input and digital output functions
AnalogIn   ain(PA_0, V_REF);
DigitalOut dout(LED1);

// Using Low Power timer because it does not block deep sleep mode
LowPowerTimer timer; 

// main() runs in its own thread in the OS
int main()
{

    printf("Running Mbed OS %d\n", MBED_MAJOR_VERSION);
    printf("ADC Vref %f\n", ain.get_reference_voltage());
    float raw = 0; 

    // Store timer reads
    // Using microseconds std::chrono types 
    microseconds time_delta; 

    // Start timer
    timer.start(); 

    while (true) {

        printf("\n Next ==> \n");
        
        led = !led; // Toggle LED

        // Sleep for defined time
        ThisThread::sleep_for(BLINKING_RATE);

        // print the percentage and 16 bit normalized values
        raw = ain.read();
        printf("raw: %g \n", raw);
        printf("voltage: %g \n", (raw*V_REF));
        printf("current: %g \n", (raw*V_REF) - V_OFFSET);

        // Read timer values 
        time_delta = timer.elapsed_time();
        printf("Elapsed time: %llu milliseconds\n", duration_cast<std::chrono::milliseconds>(time_delta).count());

    }
}

