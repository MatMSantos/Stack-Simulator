#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //toupper()

#include "include/lib.h"
#include "include/filehandler.h"

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
    while((ch=fgetc(fp))!='\n')
        if(!~ch) return -1;
    return 0;
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

    if (strcomp(extension, "sms")==0)
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

/*instruction_t readLine(FILE *fp) {

    static int line = 1;
    instruction_t inst = { .mne=NULL, .param=NULL, .line=line, .error=0};

    int numchar = 0;
    char ch;

    // Ler o mnemônico
    while (numchar<MAXSIZE_MNE)
    {
        ch = fgetc(fp);
        switch(ch)
        {   // Special cases
            case  ' ': goto ARGS;
            case '\n': if(!numchar) return inst;
            case  '#': if(!numchar) { gotoeol(fp); return inst; }
        }
        inst.mne[numchar] = ch;
        if(++numchar)
        numchar++;
    }
    ARGS:
    fgets(inst.param, MAXSIZE_PARAM+1, fp);

    line++;
    return inst;
}*/

instruction_t readLine(FILE *fp) {

    static int line = 1;
    instruction_t inst = { .mne=NULL, .param=NULL, .line=line, .error=0, .parse=1};

    char lineread[MAXSIZE_LINE];
    char *mne;
    char *ext;

    if(fgets(lineread, MAXSIZE_LINE, fp)==NULL) { inst.line=EOF; return inst; }

    // We need to make sure the file pointer is at the next line after this first read
    fseek(fp, -1L, SEEK_CUR);
    if(fgetc(fp)!='\n') gotoeol(fp);

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
    memmove(inst.mne, mne, 4);
    ext = strtok(NULL, "");
    //memmove(inst.param, ext, )

    /**
     * Some remarks to be made:
     * 
     *  - 
     * 
     */



    line++;
    return inst;
}



