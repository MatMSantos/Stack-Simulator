#ifndef LIB_H
    #define LIB_H

/**
 * TO-DO:
 * 
 * - Leitura de arquivo:
 *      - Abertura de arquivo
 *          - Leitura de linha até EOF
 *          - Linhas -> for -> struct
 *              - Espaços separam strings, strings entram nas strings do array
 *              - Não esquecer conversão de string para int16_t
 *      - 

// Definitions

/**
 * Error messages
 */
#define _ERRMSG_NOARGS "Error: no arguments, you must specify at least one. \n\nAborting the program..."

/**
 * Variables
 */
#define STACK_MAXSIZE 128

/**
 * Instruction
 *  Only one parameter needed
 */
typedef struct {
    char mne[4];   // Mnemonic
    char param[6]; // Should be converted to 16-bit integer: [-32768, 32767]
    int line;      // where instruction was read (i have c to blame for not allowing it to be static)
} instruction_t;

/**
 * Syntax errors
 */
enum { NONE, SYNTAX_ERR=4, INST_ERR, ARG_ERR, POP_ERR, PUSH_ERR } error_t;



// Function headers

/**
 * Open file
 * 
 * in: string with name of file;
 * out: pointer to file;
 * err: null pointer
 */
FILE *openFile(char *name);

/**
 * Read line from file, store in 'instruction'
 * obs: check for eof;
 *      use a 'for' loop, disconsider spaces,
 *      mne>4 chars disconsider 5+, param>6 chars disconsider whole param;
 * 
 * in:  file to be read; line number;
 * out: struct with what was read; line=EOF at eof (mne and param don't matter);
 * err: none;
 */
instruction_t readLine(FILE *f, int n);

/**
 * Check 
 * 
 * in:
 * out:
 * err:
 */
int parseInst()

/**
 * Parse arithmetic instruction
 * obs: 
 * 
 * out: 
 */
void arithmetic();

/**
 * Parse logic instruction
 * 
 * out: 
 */
void logic();

/**
 * Parse control instruction
 */
void control();

/**
 * Parse IO instruction
 */
void io();

/**
 * 
 */

/*

switch(instruction.mne){
    case 'ADD':
    case 'SUB':
    case

    case: 

    default: //Erro 001
}
*/

#endif LIB_H