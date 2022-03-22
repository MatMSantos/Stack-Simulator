#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "include/lib.h"

#define USAGE_ "%s [-f] [] "

/* 
====== STACK MACHINE SIMULATOR ======

    - Word size: 16 bit
    - Stack size: 128 words
    - Registers: $R
    - Instructions:
        - Arithmetic: 'ADD', 'SUB', 'MUL', 'DIV', 'MOD'
        - Logic: 'NOT', 'OR', 'AND', 'MIR' (mirror bits in number)
        - Control: 'PUSH', 'POP'
        - IO: 'OUT' (print top of the stack)
    - Error messages:
        - '000': Syntax error
        - '001': Invalid instruction
        - '002': Invalid argument
        - '003': 'POP' error - empty queue
        - '004': 'PUSH' error - full queue

=====================================
*/

int main(int argc, char *argv[]) {

    /* 128-word stack */
    int16_t stack[STACK_MAXSIZE];
    /* Pointer to top of the stack */
    int16_t* top;


    if (!(argc-1)) {
        printf(_ERRMSG_NOARGS);
        abort();
    }

    else {
        
        while (--argc > 0) {
            printf("\'%s\'", argv[argc]);
            if (argc!=1) printf(", ");
        }
        return EXIT_SUCCESS;
    }
}