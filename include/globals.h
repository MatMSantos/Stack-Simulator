#ifndef GLOBALS_H
    #define GLOBALS_H

    #include "filehandler.h"

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

#endif