#include <stdio.h>
#include "stackmachine.h"

int main()
{
    word_t code[] = {
	psh, 47,  /* Hello world */
	psh, 46,
	psh, 38,
	psh, 13,
	psh, 21,
	psh, 27,
	psh, 24,
	psh, 32,
	psh, 45,
	psh, 24,
	psh, 21,
	psh, 21,
	psh, 14,
	psh, 17,

	dpl,
	psh, 47,
	cmp,
	psh, 41,
	cbr,
	pop,
	out,
	pop,
	psh, 28,
	ubr,
	hlt
    };

    loadIntoMemory(code, 50, 0);
    
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
	
	default:
	    puts("Encountered an invalid opcode during runtime.");
	}

    } while (MEMORY[INC_CST] != hlt);
    
    return 0;
}
