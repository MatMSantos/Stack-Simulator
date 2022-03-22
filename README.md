# Stack-Simulator
Stack machine architecture designed in C, complete with its own Assembly language and four example programs.

### How to use:
- Reads .msm assembly files, written using the instructions described below.

### Features:
- 16-bit word size
- 128 word stack
- 12 instructions, divided into four categories:
    - Arithmetic: 'ADD', 'SUB', 'MUL', 'DIV', 'MOD'
    - Logic: 'NOT', 'OR', 'AND', 'MIR' (mirror bits in number)
    - Control: 'PUSH', 'POP'
    - IO: 'OUT' (print top of the stack)
- Syntax error

***

### How it works:


### Next on the list:

- Program arguments:
    - '-F': prints output to a file

- Functions:
    - Checks if argument '-F' was passed. Returns 1 if it was, 0 if it was not.
