#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "include/lib.h"

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

    int iter = 0;

    if (!argc) {
        printf(_ERRMSG_NOARGS);
        abort();
    }

    else {
        
        if(argc==1) printf("There is %d argument passed: ", argc);
        else printf("There are %d arguments passed: ", argc);

        for (; iter < argc; iter++) {
            printf("\'%s\'", argv[iter]);
            if ( (argc-iter)>1 ) printf(", ");
        }

        exit(EXIT_SUCCESS);
    }
}