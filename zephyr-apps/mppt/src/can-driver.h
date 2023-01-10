#include <zephyr/logging>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/can.h>

#define SUCCESS 1

//
void initialize_CAN();

void read_CAN_signal();

int8_t write_CAN_signal(int msg);
