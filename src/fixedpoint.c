#include <stdint.h>
#include <math.h>

#include "../include/fixedpoint.h"

double fixed_to_double(int16_t input)
{
    return((double) input) / (double)(1 << FIXED_POINT_FRACTIONAL_BITS);
}

int16_t double_to_fixed(double input)
{
    return (uint16_t)(round(input * (1<<FIXED_POINT_FRACTIONAL_BITS)));
}