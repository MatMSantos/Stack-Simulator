#include "../include/globals.h"

/**
 * File handler
 */
label_t g_listoflabels[MAXNUM_LABELS];
int g_labelindex = 0;

/**
 * Instructions
 */
int g_execute = 1;
int g_jump = 0;
int g_jumpto = 0;

/**
 * Stack
 */
int16_t  g_memreg[MEMREGSIZE];
int16_t  g_regr;
int16_t  g_stack[STACK_MAXSIZE];
int16_t *g_stacktop;