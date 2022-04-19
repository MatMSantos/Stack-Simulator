#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "include/debug.h"
#include "include/globals.h"
#include "include/filehandler.h"
#include "include/instructions.h"
#include "include/fixedpoint.h"

int hasalpha(char *str)
{
    int iter;
    for(iter=0; iter<strlen(str); iter++)
    {
        if(isalpha(str[iter])) return 1;
    }
    return 0;
}

int searchlabels(char *label)
{
    int iter;

    for(iter=0; iter<MAXNUM_LABELS; iter++)
    {
        if(strcmp(g_listoflabels[iter].name, label)==0)
        {
            return g_listoflabels[iter].line+1;
        }
    }
    return 0;
}

instruction_t arithmetic(instruction_t inst, int opt)
{
    double above;
    double below;

    // First, check if there are more than two arguments in the instruction
    if(inst.has_garbage)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return inst;
    }

    // Syntax error:
    // Arithmetic operations have no operands
    if(strlen(inst.param)!=0)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return inst;
    }

    // Runtime error:
    // Can't perform arithmetic operations on an empty stack or with only one value
    if(STACK_ISEMPTY || g_stacktop==g_stack)
    {
        if (opt!=LN && opt!=EXP)
        {
            // Return error
            inst.runerror = RUNERR_UNDEF_ARG;
            // Halt execution
            HALT;
            return inst;
        }
    }

    if(IS_HALTED) return inst;
    else
    {
        // Initializations before arithmetic operations
        above = fixed_to_double(STACKTOP(0));
        below = fixed_to_double(STACKTOP(1));

        switch(opt)
        {
            case ADD:
                g_regr = double_to_fixed(above+below);
                break;
            case SUB:
                g_regr = double_to_fixed(above-below);
                break;
            case MUL:
                g_regr = double_to_fixed(above*below);
                break;
            case DIV:
                if(STACKTOP(1)==0)
                {
                    inst.runerror = RUNERR_DIV_BY_ZERO;
                    HALT;
                    return inst;
                }
                else g_regr = double_to_fixed(above/below);
                break;
            case POW:
                g_regr = double_to_fixed(pow(above, below));
                break;
            case MOD:
                g_regr = double_to_fixed(fmod(above, below));
                break;
            case LN:
                g_regr = double_to_fixed(log(above));
                break;
            case EXP:
                g_regr = double_to_fixed(exp(above));
                break;
            default: // Hopefully it will never get to this
                break;
        }
    }

    return inst;
}

instruction_t logic(instruction_t inst, int opt)
{

    // First, check if there are more than two arguments in the instruction
    if(inst.has_garbage)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return inst;
    }

    // Syntax error:
    // Logic operations have no operands
    if(strlen(inst.param)!=0)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return inst;
    }

    // Runtime error:
    // Can't perform logic operations on an empty stack
    if(STACK_ISEMPTY)
    {
        // Return error
        inst.runerror = RUNERR_UNDEF_ARG;
        // Halt execution
        HALT;
        return inst;
    }

    if(IS_HALTED) return inst;

    else
    {
        // Used in MIR operation
        int cpy = STACKTOP(0);
        int rev;
        int iter=(sizeof(int16_t)*8)-1;

        switch (opt)
        {
            case NOT:
                g_regr = ~STACKTOP(0);
                break;
            case OR:
                if(g_stacktop==g_stack)
                {
                    // Return error
                    inst.runerror = RUNERR_UNDEF_ARG;
                    // Halt execution
                    HALT;
                    return inst;
                }
                g_regr = STACKTOP(0) | STACKTOP(1);
                break;
            case AND:
                if(g_stacktop==g_stack)
                {
                    // Return error
                    inst.runerror = RUNERR_UNDEF_ARG;
                    // Halt execution
                    HALT;
                    return inst;
                }
                g_regr = STACKTOP(0) & STACKTOP(1);
                break;
            case MIR:
                for(; iter >= 0; iter--){
                    rev |= (cpy & 1) << iter;
                    cpy >>= 1;
                }
                g_regr = rev;
                break;
            default:
                break;
        }
    }

    return inst;
}

instruction_t control(instruction_t inst, int opt)
{
    double value;
    int reg;

    // First, check if there are more than two arguments in the instruction
    if(inst.has_garbage)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return inst;
    }

    if(strchr(inst.param, '+'))
    {
        // Return error
        inst.runerror = RUNERR_ARG_OVERFLOW;
        // Halt execution
        HALT;
        return inst;
    }

    switch(opt)
    {
        // Types of errors:
        // Overflow, Syntax error (2 args)
        case PUSH:
            if(strlen(inst.param)==0 || strlen(inst.param2)!=0)
            {
                inst.synerror = SYNERR_SYNTAX;
                HALT;
                return inst;
            }
            if(STACK_ISFULL)
            {
                inst.synerror = SYNERR_PUSH;
                HALT;
                return inst;
            }
            if(!strcmp(inst.param, "$R") && !IS_HALTED)
            {
                if(g_stacktop==NULL) g_stacktop = g_stack;
                else g_stacktop++;
                STACKTOP(0) = g_regr;
            }
            else
            {
                value = atof(inst.param);
                if(hasalpha(inst.param) && strcmp(inst.param, "$R") && !value)
                {
                    inst.synerror = SYNERR_ARG;
                    HALT;
                    return inst;
                }
                if(value<FP_MINVALUE || value>FP_MAXVALUE)
                {
                    inst.runerror = RUNERR_ARG_OVERFLOW;
                    HALT;
                    return inst;
                }
                else if(!IS_HALTED)
                {
                    if(g_stacktop==NULL) g_stacktop = g_stack;
                    else g_stacktop++;
                    STACKTOP(0) = double_to_fixed(value);
                }
            }
            break;
        case POP:
            // POP takes no argument
            if(strlen(inst.param)!=0)
            {
                inst.synerror = SYNERR_SYNTAX;
                HALT;
                return inst;
            }
            if(STACK_ISEMPTY)
            {
                inst.synerror = SYNERR_POP;
                HALT;
                return inst;
            }
            else if(g_stacktop==g_stack) { if(!IS_HALTED) g_stacktop = NULL; }
            else if(!IS_HALTED) g_stacktop--;
            break;
        case MOV:
            // MOV takes two arguments
            if(strlen(inst.param2)==0 || strlen(inst.param)==0)
            {
                inst.synerror = SYNERR_SYNTAX;
                HALT;
                return inst;
            }

            reg = atoi(inst.param);
            if(strcmp(inst.param, "$R")==0)
            {
                reg = atoi(inst.param2);
                if(reg>0 && reg<=4) { if(!IS_HALTED) g_memreg[reg-1]=g_regr; }
                else
                {
                    inst.synerror = SYNERR_ARG;
                    HALT;
                    return inst;
                }
            }
            else if(reg>0 && reg<=4)
            {
                if(strcmp(inst.param2, "$R")==0) { if(!IS_HALTED) g_regr=g_memreg[reg-1]; }
                else
                {
                    inst.synerror = SYNERR_ARG;
                    HALT;
                    return inst;
                }
            }
            else
            {
                inst.synerror = SYNERR_ARG;
                HALT;
                return inst;
            }
            break;
        default:
            break;
    }

    return inst;
}

instruction_t io(instruction_t inst, int opt)
{

    // First, check if there are more than two arguments in the instruction
    if(inst.has_garbage)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return inst;
    }

    // Syntax error:
    // IO operations have no operands
    if(strlen(inst.param)!=0)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return inst;
    }

    if(IS_HALTED) return inst;

    else
    {
        switch(opt)
        {
            case OUT:
                printf("\n==> Top of the stack: %f\n\n", fixed_to_double(STACKTOP(0)));
                break;
            default:
                break;
        }
    }

    return inst;
}

instruction_t branch(instruction_t inst, int opt)
{
    int line;
    char *labelname = inst.param;

    // First, check if there are more than two arguments in the instruction
    if(inst.has_garbage)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return inst;
    }

    if(strlen(inst.param)==0 || strlen(inst.param2)!=0)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return inst;
    }

    switch(opt)
    {
        case JMP:
            if( (line=searchlabels(labelname)) && !IS_HALTED) { g_jump = 1; g_jumpto = line; }
            else
            {
                inst.runerror = RUNERR_UNDEF_LABEL;
                HALT;
                return inst;
            }
            break;
        case BZ:
            if(g_regr==0)
            {
                if( (line=searchlabels(labelname)) && !IS_HALTED) { g_jump = 1; g_jumpto = line; }
                else
                {
                    inst.runerror = RUNERR_UNDEF_LABEL;
                    HALT;
                    return inst;
                }
            }
            break;
        case BNZ:
            if(g_regr!=0)
            {
                if( (line=searchlabels(labelname)) && !IS_HALTED) { g_jump = 1; g_jumpto = line; }
                else
                {
                    inst.runerror = RUNERR_UNDEF_LABEL;
                    HALT;
                    return inst;
                }
            }
            break;
        default:
            break;
    }

    return inst;
}

instruction_t stack(instruction_t inst, int opt)
{
    if(strlen(inst.param)!=0)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return inst;
    }

    if(IS_HALTED) return inst;

    else switch(opt)
    {
        case CLEAR:
            clearstack();
        default:
            break;
    }

    return inst;
}

void clearstack(void)
{
    if(IS_HALTED) return;

    else
    {
        int iter;
        for(iter=0; iter<STACK_MAXSIZE; iter++)
        {
            g_stack[iter]=0;
        }
        g_stacktop = NULL;
    }
}

instruction_t parseinst(instruction_t inst)
{
    // It could be a BST, but this works too.
    if(inst.mne[0]=='A')
    {
        if(!strcmp(inst.mne, "AND")) inst = arithmetic(inst, AND);
        else if(!strcmp(inst.mne, "ADD")) inst = arithmetic(inst, ADD);
        else inst.synerror = SYNERR_INST;
    }
    else if(inst.mne[0]=='B')
    {
        if(!strcmp(inst.mne, "BNZ")) inst = branch(inst, BNZ);
        else if(!strcmp(inst.mne, "BZ")) inst = branch(inst, BZ);
        else inst.synerror = SYNERR_INST;
    }
    else if(inst.mne[0]=='C')
    {
        if(!strcmp(inst.mne, "CLEAR")) inst = stack(inst, CLEAR);
        else inst.synerror = SYNERR_INST;
    }
    else if(inst.mne[0]=='D')
    {
        if(!strcmp(inst.mne, "DIV")) inst = arithmetic(inst, DIV);
        else inst.synerror = SYNERR_INST;
    }
    else if(inst.mne[0]=='E')
    {
        if(!strcmp(inst.mne, "EXP")) inst = arithmetic(inst, EXP);
        else inst.synerror = SYNERR_INST;
    }
    else if(inst.mne[0]=='J')
    {
        if(!strcmp(inst.mne, "JMP")) inst = branch(inst, JMP);
        else inst.synerror = SYNERR_INST;
    }
    else if(inst.mne[0]=='L')
    {
        if(!strcmp(inst.mne, "LN")) inst = arithmetic(inst, LN);
        else inst.synerror = SYNERR_INST;
    }
    else if(inst.mne[0]=='M')
    {
        if(!strcmp(inst.mne, "MIR")) inst = logic(inst, MIR);
        else if(!strcmp(inst.mne, "MOD")) inst = arithmetic(inst, MOD);
        else if(!strcmp(inst.mne, "MOV")) inst = control(inst, MOV);
        else if(!strcmp(inst.mne, "MUL")) inst = arithmetic(inst, MUL);
        else inst.synerror = SYNERR_INST;
    }
    else if(inst.mne[0]=='N')
    {
        if(!strcmp(inst.mne, "NOT")) inst = logic(inst, NOT);
        else inst.synerror = SYNERR_INST;
    }
    else if(inst.mne[0]=='O')
    {
        if(!strcmp(inst.mne, "OR")) inst = logic(inst, OR);
        else if(!strcmp(inst.mne, "OUT")) inst = io(inst, OUT);
        else inst.synerror = SYNERR_INST;
    }
    else if(inst.mne[0]=='P')
    {
        if(!strcmp(inst.mne, "PUSH")) inst = control(inst, PUSH);
        else if(!strcmp(inst.mne, "POP")) inst = control(inst, POP);
        else if(!strcmp(inst.mne, "POW")) inst = arithmetic(inst, POW);
        else inst.synerror = SYNERR_INST;
    }
    else if(inst.mne[0]=='S')
    {
        if(!strcmp(inst.mne, "SUB")) inst = arithmetic(inst, SUB);
        else inst.synerror = SYNERR_INST;
    }

    return inst;
}