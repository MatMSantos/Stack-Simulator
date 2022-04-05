#ifndef STACK_H
    #define STACK_H

#include <stdint.h>

/**
 * Variables
 */
#define STACK_MAXSIZE 128

/**
 * Global variables
 */
int16_t  g_reg;
int16_t  g_stack[STACK_MAXSIZE];
int16_t *g_stacktop;

#endif