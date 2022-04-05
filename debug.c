#include<stdio.h>

#include "include/debug.h"
#include "include/instructions.h"

void printinst(instruction_t inst) {
    printf("===DEBUG===\nInstruction: \n\n");
    printf("MNE: %s\n", inst.mne);
    printf("PARAM: %s\n", inst.param);
    printf("LINE: %d\n", inst.line);
    printf("ERROR: %d\n", inst.error);
    printf("PARSE: %d\n\n", inst.parse);
}