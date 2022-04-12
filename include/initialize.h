#ifndef INITIALIZE_H
    #define INITIALIZE_H

#include <stdio.h>

/**
 * Clear all registers
 * 
 * in: none;
 * out: none;
 * err: none;
 */
void init(void);

/**
 * Store all labels in the file
 * 
 * in: pointer to file;
 * out: none;
 * err: none;
 */
void scanlabelsinfile(FILE *fp);

#endif