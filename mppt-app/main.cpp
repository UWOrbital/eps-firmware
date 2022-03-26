#include "mbed.h"
#include <cstdint>
#include <cstdio>

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

// main() runs in its own thread in the OS
int main()
{

    printf("Running Mbed OS %d\n", MBED_MAJOR_VERSION);
    printf("ADC Vref %f\n", ain.get_reference_voltage());
    float raw = 0; 

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
    }
}

