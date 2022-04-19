#ifndef FIXEDPOINT_H
    #define FIXEDPOINT_H

#include <stdint.h>
#include <math.h>

#define FIXED_POINT_FRACTIONAL_BITS 5

/**
 * Convert from 16-bit fixed-point to double
 * 
 * in: value in 16-bit unsigned int (11.5 fixed-point)
 * out: value represented by a double
 * err: none
 */
double fixed_to_double(int16_t input);

/**
 * Convert from double to 16-bit fixed point
 * 
 * in: value in double
 * out: value represented by a 16-bit unsigned int (11.5 fixed-point)
 * err: none
 */
int16_t double_to_fixed(double input);

#endif