#include <stdio.h>
#include <string.h>

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

void init(void) {
    int iter;
    for(iter=0; iter<MEMREGSIZE; iter++)
    {
        g_memreg[iter]=0;
    }
}

void scanlabelsinfile(FILE *fp) {
    char lineread[MAXSIZE_LINE+1];
    char *label;
    int currentline=1;

    rewind(fp);
    while(fgets(lineread, MAXSIZE_LINE, fp))
    {
        if(lineread[strlen(lineread)-1]!='\n') gotoeol(fp);

        if(strchr(lineread, ':')!=NULL)
        {
            g_listoflabels[g_labelindex].line=currentline+1;
            label = strtok(lineread, ":");
            memcpy(g_listoflabels[g_labelindex].name, label, MAXSIZE_LABEL);

            g_labelindex++;
        }
    }
}

int main(int argc, char *argv[]) {

    char name[]="openfiletext.sms";
    char filename_log[]="error_log.txt";

    FILE *fp;
    instruction_t inst;
    
    fp = openFile(name);

    // INITIALIZATION
    init();
    scanlabelsinfile(fp);
    
    return 0;
}