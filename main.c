#include <stdio.h>

#include "include/filehandler.h"
#include "include/instructions.h"
#include "include/stack.h"

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
    char name[]="openfiletext.sms";
    FILE *fp;
    instruction_t inst;

    fp = openFile(name);
    while((inst=readLine(fp)).line!=EOF)
    {
        if(inst.parse) printinst(inst);
    }

    return 0;
}