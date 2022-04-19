#ifndef STACK_H
    #define STACK_H

#include <stdint.h>

#define STACK_ISEMPTY (g_stacktop==NULL)
#define STACK_ISFULL (g_stacktop==g_stack+STACK_MAXSIZE-1)
#define STACKTOP(x) (*(g_stacktop-x))

#define FP_MAXVALUE  1023.96875
#define FP_MINVALUE -1024.96875

#endif