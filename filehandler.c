#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //toupper()

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
    int result=0;

    while((ch=fgetc(fp))!='\n')
    {
        if(!~ch) break;
        if(ch!=' ') result=1;
    }
    return result;
}

void gotoline(FILE *fp, int line) {
    char ch;
    int currentline=1;

    rewind(fp);
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='\n') currentline++;
        if(currentline==line) return;
    }
}

FILE *openfile(char name[]) {

    FILE *fp;
    char namecpy[MAXSIZE_NAMELEN];
    char *file;
    char *extension = NULL;

    strcpy(namecpy, name);

    file = strtok(namecpy, ".");
    if (file==NULL)
    {
        PERROR_CUSTOM(file, _ERRMSG_NO_FILE);
        return NULL;
    }
    else extension = strtok(NULL, ".");

    if (strcmp(extension, "sms")==0)
    {
        if ((fp = fopen(name, "r"))==NULL) PERROR_STD(name, errno);
        else return fp;
    }
    else if (extension==NULL) PERROR_CUSTOM(name, _ERRMSG_NO_EXTENSION);
    else
    {
        PERROR_CUSTOM(name, _ERRMSG_WRONG_EXTENSION);
    }

    return NULL; // Error
}

// Please don't copy any of this. This is bad programming.
// I mean, it works... Mostly. But I can think of several ways I could rewrite this.
// I didn't want to start from scratch all over again, so I just kept on building upon this
// monstrosity of ineffectiveness.
instruction_t readline(FILE *fp, int jumpto) {

    static int line = 1;
    instruction_t inst = { .mne="", .param="", .param2="", .line=line, .synerror=NONE, .runerror=NONE, .parse=1, .label=0};

    char lineread[MAXSIZE_LINE+1];
    char *lp = lineread;

    char *mne;
    char  lastm;
    char *param;
    char  lastp;
    int   param_infos=0;
    char *extra;
    char  lastp2;

    // Check if there is garbage at the end of the line or it is just empty space
    int   line_has_garbage = 0;

    // Check if there was a jump called
    if(g_jump) { line = g_jumpto; gotoline(fp, jumpto); g_jump = 0; }

    if(fgets(lineread, MAXSIZE_LINE, fp)==NULL) { inst.line=EOF; return inst; }

    // We need to make sure the file pointer is at the next line after this first read
    if(lineread[strlen(lineread)-1]!='\n')
    {
        if(~fgetc(fp)) line_has_garbage = gotoeol(fp); //if not at eof
    }

    /**
     * Ignore the spaces at the start of the line. If the line consists only of spaces,
     *  then the first character in 'lineread' will be a '\0'.
     * 
     * Also, ignore the line if it's a commment.
     */
    ignorespaces(&lp);
    if(*lp=='#'||*lp=='\0'||*lp=='\n') { line++; inst.parse=0; return inst; }

    stoupper(lineread);

    mne = strtok(lineread, " ");
    if(mne)
    {
        lastm = mne[strlen(mne)-1];

        if(lastm=='\n') mne[strlen(mne)-1]='\0';
    }

    param = strtok(NULL, " ");
    if(param)
    {
        lastp = param[strlen(param)-1];
        ignorespaces(&param);

        if(lastp=='\n') param[strlen(param)-1]='\0';
    }

    extra = strtok(NULL, " ");
    if(extra)
    {
        lastp2 = extra[strlen(extra)-1];
        ignorespaces(&extra);

        if(lastp2=='\n') extra[strlen(extra)-1]='\0';
    }

    // Mnemonic is greater than 4 chars in size
    if(mne!=NULL)
    {
        if(strlen(mne)>MAXSIZE_MNE) mne[MAXSIZE_MNE]='\0';
        memcpy(inst.mne, mne, MAXSIZE_MNE);

        if(param!=NULL)
        {
            // Parameter is greater than 6 chars in size ('+' error)
            if(strlen(param)>MAXSIZE_PARAM) { param[MAXSIZE_PARAM]='\0'; strcat(param, "+"); param_infos++; }
            memcpy(inst.param, param, MAXSIZE_PARAM+param_infos);

            // There is more than one parameter
            if(extra!=NULL)
            {
                memcpy(inst.param2, extra, MAXSIZE_PARAM2);
            }
        }
    }

    line++;
    return inst;
}



