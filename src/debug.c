#include <stdio.h>
#include <string.h>

#include "../include/debug.h"
#include "../include/fixedpoint.h"
#include "../include/instructions.h"
#include "../include/globals.h"

void _printinst(instruction_t inst) {
    printf("===DEBUG===\nInstruction: \n\n");
    printf("\tMNE: %s\n", inst.mne);
    printf("\tPARAM 1: %s\n", inst.param);
    printf("\tPARAM 2: %s\n", inst.param2);
    printf("\tHAS GARBAGE: %d\n", inst.has_garbage);
    printf("\tLINE: %d\n", inst.line);
    if(inst.synerror!=0) {
    printf("\tSYNTAX ERROR: %d (%03d)\n", inst.synerror, inst.synerror-1); }
    else {
    printf("\tSYNTAX ERROR: %d (%03d)\n", inst.synerror, inst.synerror); }
    printf("\tRUNTIME ERROR: %d\n", inst.runerror);
    printf("\tPARSE: %d\n\n", inst.parse);
}

void _check(void) {
    printf("-> Okay <-\n");
}

void _statusstack(void) {
    int iter;
    printf("=== STACK ===\n");
    printf("[ ");
    for (iter=0; iter<STACK_MAXSIZE; iter++)
    {
        printf("%.3f", fixed_to_double(g_stack[iter]));
        if( (iter!=0 && iter!=STACK_MAXSIZE-1) && (iter+1)%8==0) printf("\n  ");
        else printf(" ");
    }
    printf("]\n");
    printf("=============\n\n");
}

void _statusregr(void) {
    printf("=== $R: %.3f ===\n\n", fixed_to_double(g_regr));
}

void _statusmem(void) {
    int iter;
    printf("=== MEMORY ===\n");
    printf("[ ");
    for (iter=0; iter<MEMREGSIZE; iter++)
    {
        printf("%.3f ", fixed_to_double(g_memreg[iter]));
    }
    printf("]\n");
    printf("==============\n\n");
}

void _statuslabels(void) {
    int iter;
    printf("=== LABELS ===\n");
    printf("{\n");
    for (iter=0; iter<MAXNUM_LABELS; iter++)
    {
        if(strlen(g_listoflabels[iter].name)!=0)
            printf("\tLINE %d: \"%s\"\n", g_listoflabels[iter].line, g_listoflabels[iter].name);
    }
    printf("}\n");
    printf("==============\n\n");
}