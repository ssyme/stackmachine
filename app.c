#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG true
#define CHARMODE true

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
    rtn
};

static short STANDARDLIB[] = {
    dpl,
    psh, 255,
    zbr,
    out,
    pop,
    psh, 0,
    psh, 244,
    zbr,
    rtn
};

void load_prog(short program[], short length, bool start);
void print_debug(short cur_inst);

int main(void)
{
    short instr, op1, op2;
    short code[] =
	{
	    psh, 0,
	    psh, 47,
	    psh, 24,
	    psh, 21,
	    psh, 21,
	    psh, 14,
	    psh, 17,
	    psh, 0,
	    psh, 244,
	    zbr,
	    hlt
	};
    
    DATASTACK = malloc(STACK_DEPTH*sizeof(short));
    CALLSTACK = malloc(STACK_DEPTH*sizeof(short));

    MEMORY = malloc(MEMORY_SIZE*sizeof(short));

    load_prog(STANDARDLIB, 12, false);
    load_prog(code, 20, true);
    
    while ((instr = MEMORY[CALLSTACK[INSTPTR]++]))
    {
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
	    if (!CHARMODE)
	    {
		printf("%d\n", DATASTACK[DATAPTR]);
		break;
	    }

	    op1 = DATASTACK[DATAPTR];
	    if (op1 > 0 && op1 < 65)
		printf("%c", CHARSET[op1]);
	    else
		printf("<invalid character '%d'!>\n", op1);
	    if (DEBUG) puts("");
	    break;

	case (zbr):
	    op1 = DATASTACK[DATAPTR--]; op2 = DATASTACK[DATAPTR--];
	    if (!op2)
		CALLSTACK[++INSTPTR] = op1;
	    break;

	case (rtn):
	    INSTPTR--;
	    break;
	    
	default:
	    printf("<invalid opcode '%d'!>\n", instr);
	    break;
	}
	if (DEBUG) print_debug(instr);
    }
    
    free(DATASTACK);
    free(CALLSTACK);
    free(MEMORY);
    return 0;
}

void load_prog(short program[], short length, bool start)
{
    int offset = start ? 0 : MEMORY_SIZE-length;

    for (int i = 0; i < length; i++)
	MEMORY[i+offset] = program[i];
}

void print_debug(short cur_inst)
{
    printf("%d: %d [", CALLSTACK[INSTPTR]-1, cur_inst);
    for (int i = 0; i < DATAPTR; i++)
	printf(" %d", DATASTACK[i]);
    printf(" ]\n");
}
