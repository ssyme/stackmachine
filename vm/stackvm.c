#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void load_prog(short program[], short length, bool start);
void print_debug(short cur_inst);

int main(void)
{
    short instr, op1, op2;
    short code[] =
    {
	psh, 10,
	psh, 5,
	add,
	out,
	htl
    };
    
    DATASTACK = malloc(STACK_DEPTH*sizeof(short));
    CALLSTACK = malloc(STACK_DEPTH*sizeof(short));

    MEMORY = malloc(MEMORY_SIZE*sizeof(short));

    load_prog(STANDARDLIB, 22, false);
    load_prog(code, 11, true);
    
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
		printf("invalid character '%d'!\n", op1);
	    if (DEBUG) puts("");
	    break;

	case (zbr):
	    op1 = DATASTACK[DATAPTR--]; op2 = DATASTACK[DATAPTR--];
	    if (!op2)
		CALLSTACK[++INSTPTR] = op1;
	    break;

	case (rtz):
	    if (!DATASTACK[DATAPTR--]) INSTPTR--;
	    break;
	    
	default:
	    printf("invalid opcode '%d'!\n", instr);
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
    printf("(%d)\t%d\t[", CALLSTACK[INSTPTR]-2, cur_inst);
    for (int i = 0; i <= DATAPTR; i++)
	printf(" %d", DATASTACK[i]);
    printf(" ]\n");
}
