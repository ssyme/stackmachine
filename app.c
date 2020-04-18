#include <stdio.h>
#include "spec.h"
#include "vm.h"

void load_into_memory(processor_t*, word_t*, int);

int main(void)
{
	processor_t* processor = create_processor();

	word_t code[] = {push, 50, push, 34, push, 66, add, add, out, halt};
	load_into_memory(processor, code, 10);

	while (processor->active)
		cycle(processor);

	free_processor(processor);
	return 0;
}

void load_into_memory(processor_t* processor, word_t* code, int codelen)
{
	for (int i = 0; i < codelen; i++)
		processor->memory[i] = code[i];
}
