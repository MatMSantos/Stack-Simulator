#ifndef MAIN_H
    #define MAIN_H

#include "stack.h"

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
#define _ERRMSG_SYNERR_NUM "Error: found %d syntax/runtime errors in the source code."

#define _ERRMSG_SYNERR(x) "Syntax error x in line "

#endif