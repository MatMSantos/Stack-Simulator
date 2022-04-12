#ifndef FILEHANDLER_H
    #define FILEHANDLER_H

#include <stdio.h>

#include "main.h"
#include "instructions.h"

#define PERROR_STD(name, errno) (fprintf(stderr, "Could not open \"%s\": %s\n", name, strerror(errno)))
#define PERROR_CUSTOM(name, message) (fprintf(stderr, "Could not open \"%s\": %s\n", name, message))

#define _ERRMSG_NO_FILE "No file specified"
#define _ERRMSG_NO_EXTENSION "No extension associated with the file"
#define _ERRMSG_WRONG_EXTENSION "Unsupported extension"

#define MAXSIZE_NAMELEN 30
#define MAXSIZE_LINE 14
#define MAXSIZE_LABEL 8

#define MAXNUM_LABELS 100

typedef struct {
    char name[MAXSIZE_LABEL+1];
    int line;
} label_t;

/**
 * Global variables
 */
label_t g_listoflabels[MAXNUM_LABELS];
int g_labelindex = 0;

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
 * out: byte flag where bit 0 is set if there are NOT only spaces;
 * err: none;
 */
int gotoeol(FILE *fp);

/**
 * Go to specific line in the file
 * 
 * in: pointer to file; line number;
 * out: none;
 * err: none;
 */
void gotoline(FILE* fp, int line);

/**
 * Open file
 * 
 * in: string with name of file;
 * out: pointer to file;
 * err: null pointer
 */
FILE *openfile(char name[]);

/**
 * Read line from file, store in 'instruction'
 * 
 * in:  file to be read; line number;
 * out: struct with what was read (and if there was an error);
 *      line=EOF at eof (mne and param don't matter);
 * err: none;
 */
instruction_t readline(FILE *fp, int jumpto);

#endif