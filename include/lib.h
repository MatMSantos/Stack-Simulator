#ifndef LIB_H
    #define LIB_H

#include <stdint.h>

/**
 * TO-DO:
 * 
 * - Leitura de arquivo:
 *      - Abertura de arquivo
 * 
 *      - Leitura de linha até EOF
 *      - Linhas -> for -> struct
 *          - Espaços separam strings, strings entram nas strings do array
 *          - Não esquecer conversão de string para short
 *      - Procura por erros na struct
 *      - Caso não haja erros, fazer a operação
 *      - Caso haja:
 *          - Abrir um arquivo novo (-F)
 *          - Escrever a linha e o tipo de erro
 */

/**
 * Error messages (bash)
 */
#define _ERRMSG_NOARGS "Error: no arguments, you must specify at least one. \n\nAborting the program..."
#define _ERRMSG_SYNERR "Error: found %d syntax errors in the source code."

#define _EN_ERRMSG_SYNERR_000 "Syntax error. Instructions expect either zero (POP) or one operand (PUSH $R)"
#define _EN_ERRMSG_SYNERR_001 "Invalid instruction."
#define _EN_ERRMSG_SYNERR_002 "Invalid arguments."
#define _EN_ERRMSG_SYNERR_003 "Tried to POP while stack was empty."
#define _EN_ERRMSG_SYNERR_004 "Tried to PUSH while stack was full."

#define _PT_ERRMSG_SYNERR_000 "Erro de Sintaxe. É esperado que as instruções possuam zero (POP) ou um operandos (PUSH $R)."
#define _PT_ERRMSG_SYNERR_001 "Instrução inválida. Ex. POOP em vez de POP."
#define _PT_ERRMSG_SYNERR_002 "Argumento inválido. Conferir se o argumento (parâmetro) condiz com as instruções (ex. Indicar erro se \"ADD $R\")."
#define _PT_ERRMSG_SYNERR_003 "POP em queue vazia."
#define _PT_ERRMSG_SYNERR_004 "PUSH em queue cheia."

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

    int  line;     // where instruction was read
    int  error;    // type of error caught

    int  parse;    // if instruction should be parsed or not
} instruction_t;

/**
 * Syntax errors
 */
enum { NONE, SYNTAX_ERR=8, INST_ERR, ARG_ERR, POP_ERR, PUSH_ERR } error_t;

/**
 * Global variables
 */
short  g_reg;
short  g_stack[STACK_MAXSIZE];
short *g_stacktop;

// Function headers

/**
 * Clear stack
 * 
 * in: none;
 * out: none;
 * err: none;
 */
void clearStack(void);




/**
 * PARSING OF INSTRUCTIONS
 * 
 * 1. Check for errors
 *      y: send error back in struct.errror, suspend current and further instructions
 *      n: execute instruction
 */


/**
 * 
 */


/**
 * 
 * 
 * in: 
 * out:
 * err:
 */
int parseInst();

/**
 * Parse arithmetic instruction
 * obs: arithmetic instructions take 
 * 
 * in:
 * out:
 * err: 
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
 *
 * in:  
 * out:
 * err:
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