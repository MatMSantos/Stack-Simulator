#ifndef INSTRUCTIONS_H
    #define INSTRUCTIONS_H

#include "include/stack.h"

#define MAXSIZE_MNE 4
#define MAXSIZE_PARAM 6

/**
 * Instruction
 * Takes one parameter maximum
 */
typedef struct {
    char mne[MAXSIZE_MNE+1];   // Mnemonic
    char param[MAXSIZE_PARAM+3];
    // Should be converted to 16-bit integer: [-32768, 32767]
    // Param is 9 chars in size to account for syntax errors:
    // pppppp/'+'/'e' where '+' means parameter exceeds max size and 'e' means more than one parameter

    int  line;     // where instruction was read
    int  error;    // type of error caught

    int  parse;    // if instruction should be parsed or not
} instruction_t;

/**
 * Syntax errors
 */
enum { NONE, SYNTAX_ERR=8, INST_ERR, ARG_ERR, POP_ERR, PUSH_ERR } error_t;

/**
 * PARSING OF INSTRUCTIONS
 * 
 * 1. Check for errors
 *      y: send error back in struct.error, suspend current and further instructions
 *      n: execute instruction
 */

/**
 * Check for valid instructions
 * 
 * in: struct with instruction;
 * out: 
 * err:
 */
int parseinst(instruction_t inst);

/**
 * Parse arithmetic instruction
 * 
 * in: struct with instruction;
 * out: none
 * err: none;
 */
void arithmetic();

/**
 * Parse logic instruction
 * 
 * in: struct with instruction;
 * out: none
 * err: none;
 */
void logic();

/**
 * Parse control instruction
 *
 * in: struct with instruction;
 * out: none
 * err: none;
 */
void control();

/**
 * Parse IO instruction
 * 
 * in: struct with instruction;
 * out: none
 * err: none;
 */
void io();

/**
 * Parse branching instruction (unconditionals & conditionals)
 * 
 * in: struct with instruction;
 * out: none
 * err: none;
 */
void branch();

/**
 * Clear stack
 * 
 * in: none;
 * out: none;
 * err: none;
 */
void clearstack(void);

/*

switch(instruction.mne){
    case 'ADD':
    case 'SUB':
    case

    case: 

    default: //Erro 001
}
*/

#endif