#include <stdio.h>
#include "stackmachine.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
	puts("Please call with filename as arg!");
	return 1;
    }
    
    FILE* fp = fopen(argv[1], "r");
    
    loadFromFile(fp);
    loadIntoMemory(CODE, MEMORY_SIZE, 0);
    
    do {
	switch (CINSTR)
	{
	case psh:
	    PSH_DATA(IMM);
	    break;
	    
	case pop:
	    POP_DATA;
	    break;
	    
	case dpl:
	{
	    word_t top = DATATOP; PSH_DATA(top);
	    break;
	}

	case swp:
	{
	    word_t top = POP_DATA, below = POP_DATA;
	    PSH_DATA(top); PSH_DATA(below);
	    break;
	}

	case cyc:
	{
	    word_t top = DATATOP;
	    for (int i = DATAHEIGHT; i > 0; i--)
		DATASTACK[i] = DATASTACK[i-1];
	    DATASTACK[0] = top;
	    break;
	}

	case add:
	{
	    word_t opa = POP_DATA; word_t result = opa + POP_DATA;
	    PSH_DATA(result);
	    break;
	}

	case cmp:
	{
	    word_t top = POP_DATA, below = POP_DATA;
	    PSH_DATA(top == below);
	    break;
	}

	case out:
	    printf("%c", CHARSET[DATATOP]);
	    break;

	case inp:
	{
	    printf("=> "); int read; scanf("%d", &read);
	    PSH_DATA((word_t) read);
	    break;
	}

	case cbr:
	{
	    word_t brnadd = POP_DATA;
	    if (DATATOP)
		PSH_CST(brnadd);
	    break;
	}

	case ubr:
	    PSH_CST(POP_DATA);
	    break;

	case crt:
	    if (DATATOP)
		POP_CST;
	    break;

	case urt:
	    POP_CST;
	    break;

	case wrt:
	    if (DATATOP > (word_t) MEMORY_SIZE)
		MEMORY[DATATOP] = DATABEL;
	    else
		printf("Caught attempted memory write out of bounds %d\n", DATATOP);
	    POP_DATA; POP_DATA;
	    break;

	case lde:
	{
	    word_t cell = POP_DATA;
	    PSH_DATA(MEMORY[cell]);
	    break;
	}
	
	default:
	    puts("Encountered an invalid opcode during runtime.");
	}

    } while (MEMORY[INC_CST] != hlt);
    
    return 0;
}
