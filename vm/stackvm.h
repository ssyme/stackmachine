#ifndef STACKVM_H
#define STACKVM_H

#define DEBUG true
#define CHARMODE false

#define STACK_DEPTH 32
#define MEMORY_SIZE 256

#define CHARSET "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.<>!?'-+/* \n"

static short PURGATORY = 0;
static short DATAPTR   = 0;
static short INSTPTR   = 0;

static short *DATASTACK;
static short *CALLSTACK;

static short *MEMORY;

enum INSTRUCTION_SET
{
    hlt,
    psh,
    dpl,
    swp,
    pop,
    pll,
    add,
    out,
    zbr,
    rtz
};

static short STANDARDLIB[] = {
};

#endif
