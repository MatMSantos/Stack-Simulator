# Stack-Simulator
Stack machine architecture designed in C, complete with its own Assembly language and four example programs.

### How to use:
- Reads .msm assembly files, written using the instructions described below.
- Syntax: stack-simulator [-l] some_program.sms
    <Br>[-l]: print log to screen

### Features:
- 16-bit word size
- 128 word stack
- 20 instructions, divided into six categories:
    - Arithmetic: (all operations performed with top of the stack preceding value below)
                  <Br>'ADD' (addition),
                  <Br>'SUB' (subtraction),
                  <Br>'MUL' (multiplication),
                  <Br>'DIV' (division),
                  <Br>'POW' (power),
                  <Br>'MOD' (modulus),
                  <Br>'LN'  (natural logarithm),
                  <Br>'EXP' (exponential base e)
    - Logic: 'NOT' (bitwise not operation),
             <Br>'OR' (bitwise or operation),
             <Br>'AND' (bitwise and operation),
             <Br>'MIR' (mirror bits in number)
    - Control: 'PUSH' (push to stack),
               <Br>'POP' (pop from stack),
               <Br>'MOV' (move from register->memory or memory->register)
    - Branching: 'JMP' (jump to label),
                 <Br>'BZ' (branch to label if zero),
                 <Br>'BNZ' (branch to label if not zero)
    - IO: 'OUT' (print top of the stack)
    - Stack: 'CLEAR' (clears the stack)
- Syntax/runtime error handling

***