#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //toupper()

#include "include/lib.h"
#include "include/filehandler.h"
#include "include/instructions.h"

void ignorespaces(char **str) {
    while(**str==' ') (*str)++;
}

void stoupper(char *str) {
    while(*str)
    {
        *str = toupper((unsigned char) *str);
        str++;
    }
}

int gotoeol(FILE *fp) {
    char ch;
    int comment=0;

    // 0000 0010: onlyspaces
    int result=2;

    while((ch=fgetc(fp))!='\n')
    {
        if(!~ch) { result|=1; break; }
        if(ch=='#') comment=1;
        if(!comment&&(result&2)) if(ch!=' ') result&=1;
    }
    return result; //bit 1: spaces, bit 0: eof
}

FILE *openFile(char name[]) {

    FILE *fp;
    char *file;
    char *extension = NULL;

    file = strtok(name, ".");
    if (file==NULL)
    {
        PERROR_CUSTOM(file, _ERRMSG_NO_FILE);
        return NULL;
    }
    else extension = strtok(NULL, ".");

    if (strcmp(extension, "sms")==0)
    {
        if ((fp = fopen(file, "r"))==NULL) PERROR_STD(file, errno);
        else return fp;
    }
    else if (extension==NULL) PERROR_CUSTOM(file, _ERRMSG_NO_EXTENSION);
    else
    {
        PERROR_CUSTOM(file, _ERRMSG_WRONG_EXTENSION);
    }

    return NULL; // Error
}

instruction_t readLine(FILE *fp) {

    static int line = 1;
    instruction_t inst = { .mne=NULL, .param=NULL, .line=line, .error=0, .parse=1};

    char lineread[MAXSIZE_LINE];
    char *mne;
    char *param;
    int   param_infos=0;
    char *extra;

    // Requires bit manipulation because i need two values from gotoeol.
    // Basically it's too cumbersome to return an array or a struct, and I don't want to allocate
    // any byte in the memory
    int   line_info;

    if(fgets(lineread, MAXSIZE_LINE, fp)==NULL) { inst.line=EOF; return inst; }

    // We need to make sure the file pointer is at the next line after this first read
    fseek(fp, -1L, SEEK_CUR);
    if(fgetc(fp)!='\n') line_info = gotoeol(fp);

    /**
     * Ignore the spaces at the start of the line. If the line consists only of spaces,
     *  then the first character in 'lineread' will be a '\0'.
     * 
     * Also, ignore the line if it's a commment.
     */
    ignorespaces(&lineread);
    if(*lineread=='#'||*lineread=='\0') { line++; inst.parse=0; return inst; }

    stoupper(lineread);

    mne = strtok(lineread, " ");
    param = strtok(NULL, " ");
    extra = strtok(NULL, "");

    // Mnemonic is greater than 4 chars in size
    if(strlen(mne)>MAXSIZE_MNE) mne[MAXSIZE_MNE]='\0';

    // Parameter is greater than 6 chars in size ('+' error)
    if(strlen(param)>MAXSIZE_PARAM) { param[MAXSIZE_PARAM]='\0'; strcat(param, "+"); param_infos++; }

    // There is more than one parameter ('e' error)
    if(extra) ignorespaces(&extra);
    if(extra) { strcat(param, "e"); param_infos++; }

    memcpy(inst.mne, mne, MAXSIZE_MNE);
    memcpy(inst.param, param, MAXSIZE_PARAM+param_infos);

    line++;
    return inst;
}



