#include "mbed.h"

#define BLINKING_RATE     1000ms

// Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

// main() runs in its own thread in the OS
int main()
{

    printf("Running Mbed OS %d\n", MBED_MAJOR_VERSION);

    while (true) {
        
        led = !led; // Toggle LED

        // Sleep for defined time
        ThisThread::sleep_for(BLINKING_RATE);
    }
}

