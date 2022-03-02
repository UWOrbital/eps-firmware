#include "mbed.h"

enum sensor_type {VOLTAGE = 0, CURRENT = 1};
enum sensor_bus {SPI = 0, I2C = 1, UART = 3, CAN = 4};

/**
* Class to create a sensor object to use for getting sensor data
*/
class Sensor {

    private:
        int type, bus; 

    public:

        Sensor(int type, int bus);

        float get_values();

    private:

};