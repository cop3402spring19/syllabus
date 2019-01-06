# Virtual Machine Specification

## Registers

    r0-r11 no convention, general purpose
    r12 (fp) is the frame pointer (by convention)
    r13 (sp) is the stack pointer (by convention)
    r14 (ln) is link register (holds next pc after a call)
    r15 (ip) is the instruction pointer (program counter)

## Instructions


Operands may be the following:

- dest, src, ri, rj are all place-holders for a register
- imm(ediate) is an integer given directly to the op
- disp is an offset in instruction array

These are the operations:

    // I/O
    read dest - read number from input and store in register
    wr src - write number from register

    // arithmetic
    add dest ri rj - add values in ri and rj and store in dest
    sub dest ri rj - subtract values in ri and rj and store in dest
    mul dest ri rj - multiply values in ri and rj and store in dest
    div dest ri rj - integer divide values in ri and rj and store in dest
    mod dest ri rj - take modulo of values in ri and rj and store in dest

    addi dest ri imm - add value in ri with constant imm and store in dest
    subi dest ri imm - substract value in ri with constant imm and store in dest
    muli dest ri imm - multiply value in ri with constant imm and store in dest
    divi dest ri imm - integer divide value in ri with constant imm and store in dest
    modi dest ri imm - take modulo of value in ri with constant imm and store in dest

    // compare and branch
    cmp ri rj - compare values of two registers
    cmpi ri imm - compare register to constant
    beq disp - branch if equal
    bne disp - branch if not equal
    blt disp - branch if less than
    ble disp - branch if less than or equal
    bgt disp - branch if greater than
    bge disp - branch if greater than or equal
    br disp - unconditional branch
    bl disp - branch and set link register
    ret ri - return to address in register

    // storage
    mov dest ri - move value from one register to another
    movi dest imm - store constant in a register
    ld dest ri imm - load value from memory location ri + imm to dest
    st src ri imm - store value from src to memory location ri + imm
    psh src ri - push register value onto address ri
    pop dest ri - pop register value from address ri to register dest

    // other
    nop - do nothing
    hlt - halt

## Example Pseudo-Code

`mem` is the memory array.  `reg` is the register array.  `ip` is the instruction pointer.  `ln` is the link register.  `next` is the next code index to evaluation.

Some pseudo is left as homework to fill in.

    // I/O
    read dest:         reg[dest] := read number from standard in
    wr src:            write reg[src] to standard out

    // arithmetic
    add dest ri rj:    reg[dest] := reg[ri] + reg[rj]
    sub dest ri rj:    ?
    mul dest ri rj:    ?
    div dest ri rj:    ?
    mod dest ri rj:    ?

    addi dest ri imm:  reg[dest] := reg[ri] + imm
    subi dest ri imm:  ?
    muli dest ri imm:  ?
    divi dest ri imm:  ?
    modi dest ri imm:  ?

    // compare and branch
    cmp ri rj:         z := reg[ri] == reg[rj] ? 1 : 0
                       n := reg[ri] < reg[rj] ? 1 : 0
    cmpi ri imm:

    beq disp:          if (z) next := ip + disp
    bne disp:          if (!z) next := ip + disp
    blt disp:          if (n) next := ip + disp
    ble disp:          ?
    bgt disp:          ?
    bge disp:          ?
    br disp:           ?
    bl disp:           ln := ip + 1; next = ip + disp
    ret ri:            next := ?

    // storage
    mov dest ri:       ?
    movi dest imm:     ?
    ld dest ri imm:    reg[dest] = mem[reg[ri]] + imm
    st src ri imm:     ?
    psh src ri:        reg[ri]++; mem[reg[ri]] = reg[src]
    pop dest ri:       ?  (remember that ri points to top element of stack)
