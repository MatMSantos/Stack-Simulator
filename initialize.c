#include "include/initialize.h"
#include "include/stack.h"
#include "include/filehandler.h"

void init(void) {
    int iter;
    for(iter=0; iter<MEMREGSIZE; iter++)
    {
        g_memreg[iter]=0;
    }
}

void scanlabelsinfile(FILE *fp) {
    char lineread[MAXSIZE_LINE+1];
    char *label;
    int currentline=1;

    rewind(fp);
    while(fgets(lineread, MAXSIZE_LINE, fp))
    {
        if(lineread[strlen(lineread)-1]!='\n') gotoeol(fp);

        if(strchr(lineread, ':')!=NULL)
        {
            g_listoflabels[g_labelindex].line=currentline+1;
            label = strtok(lineread, ":");
            memcpy(g_listoflabels[g_labelindex].name, label, MAXSIZE_LABEL);

            g_labelindex++;
        }
    }
}