#ifndef STACKMACHINE_H
#define STACKMACHINE_H

#define STACK_DEPTH 32
#define MEMORY_SIZE 256

#define CHARSET "0123456789ANCDEFGHIJKLMNOPQRSTUVWYZ.<>!?'-+/* \n\0"

#define PSH_CST(x) *(++CSTPTR) = x
#define POP_CST    *(CSTPTR--)
#define INC_CST    ++(*CSTPTR)

#define CINSTR MEMORY[*CSTPTR]      /* Current instruction */
#define IMM    MEMORY[++(*CSTPTR)]  /* Immediate data */

#define PSH_DATA(x) *(++DATAPTR) = x
#define POP_DATA    *(DATAPTR--)
#define DATAHEIGHT  DATAPTR-DATASTACK+1  /* Height of stack */

typedef int8_t word_t;

static word_t MEMORY[MEMORY_SIZE];

static word_t CALLSTACK[STACK_DEPTH];
static word_t DATASTACK[STACK_DEPTH];

static word_t *DATAPTR = DATASTACK;
static word_t *CSTPTR  = CALLSTACK;

enum OP_CODES
{
    nop,
    hlt,
    psh,
    pop,
    dpl,
    swp,
    cyc,
    add,
    cmp,
    out,
    inp,
    cbr,
    ubr,
    crt,
    urt
};

void loadIntoMemory(word_t program[], word_t proglen, word_t origin)
{
    for (int i = origin; i < proglen; i++)
	MEMORY[i] = program[i];
}

void printStack(void)
{
    printf("{");
    for (int i = 0; i < DATAHEIGHT; i++)
    {
	printf(" %d ", DATASTACK[i]);
    }
    puts("}");
}

#endif
