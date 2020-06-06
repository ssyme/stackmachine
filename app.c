#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG false

#define STACK_DEPTH 32
#define MEMORY_SIZE 256

static short PURGATORY;

static short DATAPTR;
static short INSTPTR;

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
    jpz
};

void load_prog(short program[], short length);

int main(void)
{
    short instr, op1, op2;
    short code[] =
	{
	    psh, 15,  // how many iterations
	    psh, 1,
	    psh, 1,

	    out,      // print first two elements
	    out,

	    dpl,      // calculate next element
	    pop,
	    add,

	    swp,      // loop
	    psh, -1,
	    add,
	    dpl,
	    psh, 28,  // halt if finished iterating
	    jpz,
	    swp,

	    out,      // print next element

	    pll,      // return to start
	    swp,
	    psh, 0,
	    psh, 8,
	    jpz,

	    hlt
	};
    
    DATAPTR = INSTPTR = PURGATORY = 0;
    DATASTACK = malloc(STACK_DEPTH*sizeof(short));
    CALLSTACK = malloc(STACK_DEPTH*sizeof(short));

    MEMORY = malloc(MEMORY_SIZE*sizeof(short));
    
    load_prog(code, 29);
    
    while ((instr = MEMORY[CALLSTACK[INSTPTR]++]))
    {
	if (DEBUG) printf("%d: %d\n", CALLSTACK[INSTPTR]-1, instr);
	switch (instr)
	{
	case (psh):
	    DATASTACK[++DATAPTR] = MEMORY[CALLSTACK[INSTPTR]++];
	    break;

	case (add):
	    op1 = DATASTACK[DATAPTR--]; op2 = DATASTACK[DATAPTR--];
	    DATASTACK[++DATAPTR] = op1 + op2;
	    break;

	case (dpl):
	    op1 = DATASTACK[DATAPTR];
	    DATASTACK[++DATAPTR] = op1;
	    break;

	case (swp):
	    op1 = DATASTACK[DATAPTR--]; op2 = DATASTACK[DATAPTR--];
	    DATASTACK[++DATAPTR] = op1;
	    DATASTACK[++DATAPTR] = op2;
	    break;
	    
	case (pop):
	    PURGATORY = DATASTACK[DATAPTR--];
	    break;

	case (pll):
	    DATASTACK[++DATAPTR] = PURGATORY;
	    break;

	case (out):
	    printf("%d\n", DATASTACK[DATAPTR]);
	    break;

	case (jpz):
	    op1 = DATASTACK[DATAPTR--]; op2 = DATASTACK[DATAPTR--];
	    if (!op2)
		CALLSTACK[++INSTPTR] = op1;
	    break;
	    
	default:
	    printf("encountered invalid opcode '%d'!\n", instr);
	    break;
	}
    }
    
    free(DATASTACK);
    free(CALLSTACK);
    free(MEMORY);
    return 0;
}

void load_prog(short program[], short length)
{
    for (int i = 0; i < length; i++)
	MEMORY[i] = program[i];
}
