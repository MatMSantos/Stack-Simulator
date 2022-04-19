#include <stdio.h>
#include <string.h>

#include "../include/debug.h"
#include "../include/main.h"
#include "../include/initialize.h"
#include "../include/instructions.h"
#include "../include/filehandler.h"

#define USAGE_ "%s [-l] [] "

/* 
====== STACK MACHINE SIMULATOR ======

    STUDENTS:
        * Leandro Reis Boniatti 00324060
        * Leonardo da Silva Junqueira 00242318
        * Lucas Mendes Chiloff 00330074
        * Mateus Moreira Santos 00243714

    - Word size: 16 bit
    - Stack size: 128 words
    - Registers: $R + 4 Memory Registers
    - Instructions:
        - Arithmetic: 'ADD', 'SUB', 'MUL', 'DIV', 'POW', 'MOD', 'LN', 'EXP'
        - Logic: 'NOT', 'OR', 'AND', 'MIR' (mirror bits in number)
        - Control: 'PUSH', 'POP', 'MOV'
        - Branching: 'JMP', 'BZ', 'BNZ'
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
    int prntlog=0;

    //char name[]="./programs/TESTE.sms";
    FILE *fp;
    instruction_t inst;

    FILE *errfp;
    char filename_log[]="error_log.txt";

    int num_errors = 0;
    errfp = fopen(filename_log, "w");

    if(argc>1)
    {
        if(strcmp(argv[1],"-l")==0) { prntlog=1; fp=openfile(argv[2]); }
        else fp=openfile(argv[1]);
    }
    else { printf("%s\n", _ERRMSG_NOARGS); return -1; }

    // INITIALIZATION
    init();
    scanlabelsinfile(fp);

    while((inst = readline(fp)).line!=EOF)
    {
        if(inst.parse)
        {
            inst = parseinst(inst);

            /*
            _printinst(inst);
            _statusstack();
            _statusregr();
            _statusmem();
            fgetc(stdin);
            */

            if(inst.synerror != SYNERR_NONE)
            {
                num_errors++;
                fprintf(errfp, _ERRMSG_SYNERR, inst.synerror-1, inst.line);

                if(prntlog) fprintf(stderr, _ERRMSG_SYNERR, inst.synerror-1, inst.line);
            }
        }
    }

    if(num_errors>0) printf(_ERRMSG_SYNERR_NUM, num_errors);

    fclose(fp);
    fclose(errfp);
    return 0;
}