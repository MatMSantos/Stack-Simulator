#ifndef GLOBALS_H
    #define GLOBALS_H

    #include <stdint.h>
    #include "filehandler.h"
    #include "stack.h"

    /**
     * File handler
     */
    extern label_t g_listoflabels[MAXNUM_LABELS];
    extern int g_labelindex;

    /**
     * Instructions
     */
    extern int g_execute;
    extern int g_jump;
    extern int g_jumpto;

    /**
     * Stack
     */
    extern uint16_t  g_memreg[MEMREGSIZE];
    extern uint16_t  g_regr;
    extern uint16_t  g_stack[STACK_MAXSIZE];
    extern uint16_t *g_stacktop;

#endif