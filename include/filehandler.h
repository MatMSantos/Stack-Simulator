#ifndef FILEHANDLER_H
    #define FILEHANDLER_H

#include <stdio.h>
#include "lib.h"

#define PERROR_STD(name, errno) (fprintf(stderr, "Could not open \"%s.sms\": %s\n", name, strerror(errno)))
#define PERROR_CUSTOM(name, message) (fprintf(stderr, "Could not open \"%s.sms\": %s\n", name, message))

#define _ERRMSG_NO_FILE "No file specified"
#define _ERRMSG_NO_EXTENSION "No extension associated with the file"
#define _ERRMSG_WRONG_EXTENSION "Unsupported extension"

#define MAXSIZE_LINE 13
#define MAXSIZE_MNE 4
#define MAXSIZE_PARAM 6

/**
 * Open file
 * 
 * in: string with name of file;
 * out: pointer to file;
 * err: null pointer
 */
FILE *openFile(char name[]);

/**
 * Read line from file, store in 'instruction'
 * obs: check for eof;
 *      use a 'for' loop, disconsider spaces,
 *      mne>4 chars disconsider 5+, param>6 chars disconsider whole param;
 * 
 * in:  file to be read; line number;
 * out: struct with what was read (and if there was an error); line=EOF at eof (mne and param don't matter);
 * err: none;
 */
instruction_t readLine(FILE *f, int n);

/**
 * Ignore spaces at the start of a string
 * 
 * in: pointer to string;
 * out: none;
 * err: none;
 */
void ignorespaces(char **str);

/**
 * Convert string to uppercase
 * 
 * in: string;
 * out: none;
 * err: none;
 */
void stoupper(char *str);

/**
 * Go to next line in the file
 * 
 * in: pointer to file;
 * out: 0 if succesfully at next line, -1 if EOF;
 * err: none;
 */
int gotoeol(FILE *fp);

#endif FILEHANDLER_H