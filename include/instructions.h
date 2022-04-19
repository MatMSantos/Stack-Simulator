#ifndef INSTRUCTIONS_H
    #define INSTRUCTIONS_H

#include "stack.h"

#define MAXSIZE_MNE 5
#define MAXSIZE_PARAM 11
#define MAXSIZE_PARAM2 3

#define HALT g_execute=0
#define IS_HALTED g_execute==0

/**
 * Instruction
 * Takes one parameter maximum
 */
typedef struct {
    char mne[MAXSIZE_MNE+1];   // Mnemonic
    char param[MAXSIZE_PARAM+3];
    char param2[MAXSIZE_PARAM2+1];

    int  has_garbage;
    // Should be converted to 16-bit integer: [-32768, 32767]
    // Param is 9 chars in size to account for syntax errors:
    // pppppp/'+'/'e' where '+' means parameter exceeds max size and 'e' means more than one parameter

    int  line;     // where instruction was read
    int  synerror;    // type of syntax error caught
    int  runerror;    // type of runtime error caught

    int  parse;    // if instruction should be parsed or not
} instruction_t;

/**
 * Arithmetic operations
 */
enum math_t { ADD, SUB, MUL, DIV, POW, MOD, LN, EXP };

/**
 * Logic operations
 */
enum logic_t { NOT, OR, AND, MIR };

/**
 * Control operations
 */
enum control_t { PUSH, POP, MOV };

/**
 * Branching operations
 */
enum branch_t { JMP, BZ, BNZ };

/**
 * IO operations
 */
enum io_t { OUT };

/**
 * Other stack operations
 */
enum stack_t { CLEAR };

/**
 * Syntax errors
 */
enum synerror_t { SYNERR_NONE, SYNERR_SYNTAX, SYNERR_INST, SYNERR_ARG, SYNERR_POP, SYNERR_PUSH };
/**
 * Runtime errors
 */
enum runerror_t { RUNERR_NONE, RUNERR_UNDEF_ARG, RUNERR_DIV_BY_ZERO, RUNERR_ARG_OVERFLOW, RUNERR_UNDEF_LABEL };

/**
 * PARSING OF INSTRUCTIONS
 * 
 * 1. Check for errors
 *      y: send error back in struct.error, suspend current and further instructions
 *      n: execute instruction
 */

/**
 * Execute arithmetic instruction
 * 
 * in: struct with instruction;
 * out: struct with instruction;
 * err: none;
 */
instruction_t arithmetic(instruction_t inst, int opt);

/**
 * Execute logic instruction
 * 
 * in: struct with instruction;
 * out: struct with instruction;
 * err: none;
 */
instruction_t logic(instruction_t inst, int opt);

/**
 * Execute control instruction
 *
 * in: struct with instruction;
 * out: struct with instruction;
 * err: none;
 */
instruction_t control(instruction_t inst, int opt);

/**
 * Execute IO instruction
 * 
 * in: struct with instruction;
 * out: struct with instruction;
 * err: none;
 */
instruction_t io(instruction_t inst, int opt);

/**
 * Execute branching instruction (unconditionals & conditionals)
 * 
 * in: struct with instruction;
 * out: struct with instruction;
 * err: none;
 */
instruction_t branch(instruction_t inst, int opt);

/**
 * Clear stack and set the top of the stack to address zero
 * 
 * in: none;
 * out: none;
 * err: none;
 */
void clearstack(void);

/**
 * Search for label in database, return number of line
 * 
 * in: label name;
 * out: line pointed by label, 0 if label not found;
 * err: none;
 */
int searchlabels(char *label);

/**
 * Check if string passed has alphabetic characters
 * 
 * in: strin;
 * out: 1 if true, 0 if false;
 * err: none;
 */
int hasalpha(char *str);

/**
 * Check for valid instructions
 * 
 * in: struct with instruction;
 * out: struct with instruction;
 * err: none;
 */
instruction_t parseinst(instruction_t inst);


#endif