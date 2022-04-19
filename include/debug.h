#ifndef DEBUG_H
 #define DEBUG_H

#include "instructions.h"

/**
 * (DEBUG) Print components of instruction
 * 
 * in: instruction;
 * out: none;
 * err: none;
 */
void _printinst(instruction_t inst);

/**
 * (DEBUG) Print "Okay" on screen
 * 
 * in: none;
 * out: none;
 * err: none;
 */
void _check(void);

/**
 * (DEBUG) Print the contents of the stack on the screen
 * 
 * in: none;
 * out: none;
 * err: none;
 */
void _statusstack(void);

/**
 * (DEBUG) Print the content of the registor $R on the screen
 * 
 * in: none;
 * out: none;
 * err: none;
 */
void _statusregr(void);

/**
 * (DEBUG) Print the contents of the memory registers on the screen
 * 
 * in: none;
 * out: none;
 * err: none;
 */
void _statusmem(void);

/**
 * (DEBUG) Print the contents of the labels on the screen
 * 
 * in: none;
 * out: none;
 * err: none;
 */
void _statuslabels(void);

#endif