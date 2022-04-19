# Stack-Simulator
Stack machine architecture designed in C, complete with its own Assembly language and four example programs.

### How to use:
- Reads .msm assembly files, written using the instructions described below.
- Syntax: stack-simulator [-l] some_program.sms
    [-l]: print log to screen

### Features:
- 16-bit word size
- 128 word stack
- 20 instructions, divided into six categories:
    - Arithmetic: (all operations performed with top of the stack preceding value below)
                  'ADD' (addition),
                  'SUB' (subtraction),
                  'MUL' (multiplication),
                  'DIV' (division),
                  'POW' (power),
                  'MOD' (modulus),
                  'LN'  (natural logarithm),
                  'EXP' (exponential base e)
    - Logic: 'NOT' (bitwise not operation),
             'OR' (bitwise or operation),
             'AND' (bitwise and operation),
             'MIR' (mirror bits in number)
    - Control: 'PUSH' (push to stack),
               'POP' (pop from stack),
               'MOV' (move from register->memory or memory->register)
    - Branching: 'JMP' (jump to label),
                 'BZ' (branch to label if zero),
                 'BNZ' (branch to label if not zero)
    - IO: 'OUT' (print top of the stack)
    - Stack: 'CLEAR' (clears the stack)
- Syntax/runtime error handling

***