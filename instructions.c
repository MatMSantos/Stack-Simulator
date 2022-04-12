#include <string.h>

#include <stdlib.h>

#include "include/filehandler.h"
#include "include/instructions.h"
#include "include/fixedpoint.h"

int searchlabels(char *label)
{
    int iter;

    for(iter=0; iter<MAXNUM_LABELS; iter++)
    {
        if(strcmp(g_listoflabels[iter].name, label)==0)
        {
            return g_listoflabels[iter].line;
        }
    }
    return 0;
}

void arithmetic(instruction_t inst, int opt)
{
    double above;
    double below;

    if(IS_HALTED) return;

    // Syntax error:
    // Arithmetic operations have no operands
    if(strlen(inst.param)!=0)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return;
    }

    // Runtime error:
    // Can't perform arithmetic operations on an empty stack or with only one value
    if(STACK_ISEMPTY || g_stacktop==g_stack)
    {
        // Return error
        inst.runerror = RUNERR_UNDEF_ARG;
        // Halt execution
        HALT;
        return;
    }

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
                return;
            } 
            else g_regr = double_to_fixed(above/below);
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

void logic(instruction_t inst, int opt)
{
    if(IS_HALTED) return;

    // Syntax error:
    // Logic operations have no operands
    if(strlen(inst.param)!=0)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return;
    }

    // Runtime error:
    // Can't perform logic operations on an empty stack
    if(STACK_ISEMPTY)
    {
        // Return error
        inst.runerror = RUNERR_UNDEF_ARG;
        // Halt execution
        HALT;
        return;
    }

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
                return;
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
                return;
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

void control(instruction_t inst, int opt)
{
    int value;
    int reg;

    if(IS_HALTED) return;

    if(strchr(inst.param, '+'))
    {
        // Return error
        inst.runerror = RUNERR_ARG_OVERFLOW;
        // Halt execution
        HALT;
        return;
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
                return;
            }
            if(STACK_ISFULL)
            {
                inst.synerror = SYNERR_PUSH;
                HALT;
                return;
            }
            if(!strcmp(inst.param, "$R"))
            {
                if(g_stacktop==NULL) g_stacktop = g_stack;
                else g_stacktop++;
                STACKTOP(0) = g_regr;
            }
            else
            {
                value = atoi(inst.param);
                if(strcmp(inst.param,"0") && value==0)
                {
                    inst.synerror = SYNERR_ARG;
                    HALT;
                    return;
                }
                if(value<FP_MINVALUE || value>FP_MAXVALUE)
                {
                    inst.runerror = RUNERR_ARG_OVERFLOW;
                    HALT;
                    return;
                }
                else
                {
                    g_stacktop++;
                    STACKTOP(0) = double_to_fixed((double) value);
                }
            }
            break;
        case POP:
            // POP takes no argument
            if(strlen(inst.param)!=0)
            {
                inst.synerror = SYNERR_SYNTAX;
                HALT;
                return;
            }
            if(STACK_ISEMPTY)
            {
                inst.synerror = SYNERR_POP;
                HALT;
                return;
            }
            else if(g_stacktop==g_stack) g_stacktop = NULL;
            else g_stacktop--;
            break;
        case MOV:
            // MOV takes two arguments
            if(strlen(inst.param2)==0 || strlen(inst.param)==0)
            {
                inst.synerror = SYNERR_SYNTAX;
                HALT;
                return;
            }

            reg = atoi(inst.param);
            if(strcmp(inst.param, "$R")==0)
            {
                reg = atoi(inst.param2);
                if(reg!=0 && (reg>0 && reg<4)) g_memreg[reg-1]=g_regr;
                else
                {
                    inst.synerror = SYNERR_ARG;
                    HALT;
                    return;
                }
            }
            else if(reg!=0 && (reg>0 && reg<4))
            {
                if(strcmp(inst.param2, "$R")==0) g_regr=g_memreg[reg-1];
                else
                {
                    inst.synerror = SYNERR_ARG;
                    HALT;
                    return;
                }
            }
            else
            {
                inst.synerror = SYNERR_ARG;
                HALT;
                return;
            }
            break;
        default:
            break;
    }
}

void io(instruction_t inst, int opt)
{
    if(IS_HALTED) return;

    // Syntax error:
    // IO operations have no operands
    if(strlen(inst.param)!=0)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return;
    }

    switch(opt)
    {
        case OUT:
            printf("\n==> Top of the stack: %f\n\n", fixed_to_double(STACKTOP(0)));
            break;
        default:
            break;
    }
}

void branch(instruction_t inst, int opt)
{
    int line;
    char *labelname = inst.param;

    if(IS_HALTED) return;

    if(strlen(inst.param)==0 || strlen(inst.param2)!=0)
    {
        inst.synerror = SYNERR_SYNTAX;
        HALT;
        return;
    }

    switch(opt)
    {
        case JMP:
            if(line=searchlabels(labelname)) { g_jump = 1; g_jumpto = line; }
            else
            {
                inst.runerror = RUNERR_UNDEF_LABEL;
                HALT;
                return;
            }
            break;
        case BZ:
            if(g_regr==0)
            {
                if(line=searchlabels(labelname)) { g_jump = 1; g_jumpto = line; }
                else
                {
                    inst.runerror = RUNERR_UNDEF_LABEL;
                    HALT;
                    return;
                }
            }
            break;
        case BNZ:
            if(g_regr!=0)
            {
                if(line=searchlabels(labelname)) { g_jump = 1; g_jumpto = line; }
                else
                {
                    inst.runerror = RUNERR_UNDEF_LABEL;
                    HALT;
                    return;
                }
            }
            break;
        default:
            break;
    }
}

void clearstack(void)
{
    int iter;
    for(iter=0; iter<STACK_MAXSIZE; iter++)
    {
        g_stack[iter]=0;
    }
    g_stacktop = NULL;
}

int parseinst(instruction_t inst)
{
    int opt;

    // It could be a BST, but this works too.
    if(inst.mne[0]=='A')
    {
        if(!strcmp(inst.mne, "AND")) arithmetic(inst, AND);
        else if(!strcmp(inst.mne, "ADD")) arithmetic(inst, ADD);
    }
    else if(inst.mne[0]=='B')
    {
        if(!strcmp(inst.mne, "BNZ")) branch(inst, BNZ);
        else if(!strcmp(inst.mne, "BZ")) branch(inst, BZ);
    }
    else if(inst.mne[0]=='C')
    {
        if(!strcmp(inst.mne, "CLEAR")) clearstack();
    }
    else if(inst.mne[0]=='D')
    {
        if(!strcmp(inst.mne, "DIV")) arithmetic(inst, DIV);
    }
    else if(inst.mne[0]=='E')
    {
        if(!strcmp(inst.mne, "EXP")) arithmetic(inst, EXP);
    }
    else if(inst.mne[0]=='J')
    {
        if(!strcmp(inst.mne, "JMP")) branch(inst, JMP);
    }
    else if(inst.mne[0]=='L')
    {
        if(!strcmp(inst.mne, "LN")) arithmetic(inst, LN);
    }
    else if(inst.mne[0]=='M')
    {
        if(!strcmp(inst.mne, "MIR")) logic(inst, MIR);
        else if(!strcmp(inst.mne, "MOD")) arithmetic(inst, MOD);
        else if(!strcmp(inst.mne, "MOV")) control(inst, MOV);
        else if(!strcmp(inst.mne, "MUL")) arithmetic(inst, MUL);
    }
    else if(inst.mne[0]=='N')
    {
        if(!strcmp(inst.mne, "NOT")) logic(inst, NOT);
    }
    else if(inst.mne[0]=='O')
    {
        if(!strcmp(inst.mne, "OR")) logic(inst, OR);
        else if(!strcmp(inst.mne, "OUT")) io(inst, OUT);
    }
    else if(inst.mne[0]=='P')
    {
        if(!strcmp(inst.mne, "PUSH")) control(inst, PUSH);
        else if(!strcmp(inst.mne, "POP")) control(inst, POP);
    }
    else if(inst.mne[0]=='S')
    {
        if(!strcmp(inst.mne, "SUB")) arithmetic(inst, SUB);
    }
    // Instruction doesn't exist
    else inst.synerror = SYNERR_INST;
}