#include <stdio.h>
#include <string.h>

#include "include/globals.h"

#include "include/main.h"
#include "include/initialize.h"
#include "include/instructions.h"
#include "include/filehandler.h"

#define USAGE_ "%s [-f] [] "

/* 
====== STACK MACHINE SIMULATOR ======

    STUDENTS:
        * Leandro Reis Boniatti 00324060
        * Leonardo da Silva Junqueira 00242318
        * Lucas Mendes Chiloff 00330074
        * Mateus Moreira Santos 00243714

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
    char filename_log[]="error_log.txt";

    FILE *fp;
    instruction_t inst;

    FILE *errfp;
    int num_errors = 0;
    
    fp = openfile(name);
    errfp = fopen(filename_log, "w");

    // INITIALIZATION
    init();
    scanlabelsinfile(fp);

    while((inst = readline(fp,0)).line!=EOF)
    {
        if(inst.parse)
        {
            inst = parseinst(inst);

            if(inst.synerror != SYNERR_NONE)
            {
                num_errors++;
                fprintf(errfp, "%s%d\n", _ERRMSG_SYNERR(inst.synerror), inst.line);
            }
        }
    }

    if(num_errors>0) printf("%s\n", _ERRMSG_SYNERR_NUM);
    return 0;
}