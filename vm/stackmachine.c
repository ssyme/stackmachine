#include <stdio.h>
#include <stdint.h>
#include "stackmachine.h"

int main()
{
    word_t code[] = {
	pop,
	psh, 1,
	psh, 2,
	psh, 3,
	psh, 4,
	psh, 5,
	cyc,
	psh, 100,
	out,
	pop,
	cyc,
	hlt
    };

    loadIntoMemory(code, 18, 0);
    
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
	    word_t top = *DATAPTR; PSH_DATA(top);
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
	    word_t top = *DATAPTR;
	    for (int i = DATAHEIGHT; i > 0; i--)
	    {
		DATASTACK[i] = DATASTACK[i-1];
	    }
	    DATASTACK[0] = top;
	    break;
	}
	
	case out:
	    printf("(%d)\n", *DATAPTR);
	    break;
	    
	default:
	    puts("Encountered an invalid opcode during runtime.");
	}
    } while (MEMORY[INC_CST] != hlt);
    
    return 0;
}
