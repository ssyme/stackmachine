#include <stdio.h>
#include "stackmachine.h"

int main()
{
    word_t code[] = {
	psh, 46,              /* Hello world program */
	psh, 38,
	psh, 24,
	psh, 21,
	psh, 21,
	psh, 14,
	psh, 17,
	psh, 7,
	swp,
	out,
	pop,
	psh, -1,
	add,
	psh, 28,
	cbr,
	psh, 16,
	ubr,
	hlt
    };

    loadIntoMemory(code, 30, 0);
    
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
	    if (!DATATOP)
		PSH_CST(brnadd);
	    break;
	}

	case ubr:
	    PSH_CST(POP_DATA);
	    break;

	case crt:
	    if (!DATATOP)
		POP_CST;
	    break;

	case urt:
	    POP_CST;
	    break;
	
	default:
	    puts("Encountered an invalid opcode during runtime.");
	}
    } while (MEMORY[INC_CST] != hlt);
    
    return 0;
}
