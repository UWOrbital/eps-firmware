#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>

float calc_dv(float t_delta, float v0, float v1);

float calc_di(float t_delta, float i0, float i1);

float measure_voltage();

float measure_current();

void init_mppt();

void run_mppt();

int calc_mppt();



