#include <stdio.h>
#include <string.h>

#include "include/debug.h"
#include "include/instructions.h"
#include "include/globals.h"

void _printinst(instruction_t inst) {
    printf("===DEBUG===\nInstruction: \n\n");
    printf("\tMNE: %s\n", inst.mne);
    printf("\tPARAM 1: %s\n", inst.param);
    printf("\tPARAM 2: %s\n", inst.param2);
    printf("\tHAS GARBAGE: %d\n", inst.has_garbage);
    printf("\tLINE: %d\n", inst.line);
    printf("\tSYNTAX ERROR: %d\n", inst.synerror);
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
    for (iter=0; iter<16; iter++)
    {
        if (iter!=0) printf("  ");
        printf("%d %d %d %d %d %d %d %d", *(g_stack+((STACK_MAXSIZE%8)*8)), *((g_stack+((STACK_MAXSIZE%8)*8))+1), *((g_stack+((STACK_MAXSIZE%8)*8))+2), *((g_stack+((STACK_MAXSIZE%8)*8))+3),
                                            *((g_stack+((STACK_MAXSIZE%8)*8))+4), *((g_stack+((STACK_MAXSIZE%8)*8))+5), *((g_stack+((STACK_MAXSIZE%8)*8))+6), *((g_stack+((STACK_MAXSIZE%8)*8))+7));
        if (iter!=15) printf("\n");
    }
    printf(" ]\n");
    printf("=============\n\n");
}

void _statusmem(void) {
    int iter;
    printf("=== MEMORY ===\n");
    printf("[ ");
    for (iter=0; iter<MEMREGSIZE; iter++)
    {
        printf("%d ", g_memreg[iter]);
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