#include<stdio.h>

#include "include/debug.h"
#include "include/instructions.h"

void printinst(instruction_t inst) {
    printf("===DEBUG===\nInstruction: \n\n");
    printf("\tMNE: %s\n", inst.mne);
    printf("\tPARAM: %s\n", inst.param);
    printf("\tLINE: %d\n", inst.line);
    printf("\tERROR: %d\n", inst.error);
    printf("\tPARSE: %d\n\n", inst.parse);
}