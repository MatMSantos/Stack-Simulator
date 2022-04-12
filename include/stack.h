#ifndef STACK_H
    #define STACK_H

#include <stdint.h>

/**
 * Variables
 */
#define STACK_MAXSIZE 128
#define STACK_ISEMPTY (g_stacktop==NULL)
#define STACK_ISFULL (g_stacktop==g_stack+STACK_MAXSIZE-1)
#define STACKTOP(x) (*(g_stacktop-x))

#define MEMREGSIZE 4

#define FP_MAXVALUE  1023.96875
#define FP_MINVALUE -1024.96875

/**
 * Global variables
 */
uint16_t  g_memreg[MEMREGSIZE];
uint16_t  g_regr;
uint16_t  g_stack[STACK_MAXSIZE];
uint16_t *g_stacktop;

#endif