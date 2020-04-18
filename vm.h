#include <stdio.h>
#include <stdlib.h>
#include "spec.h"
#include "stack.h"

typedef struct processor
{
	stack_t* data_stack;
	stack_t* call_stack;
	word_t* memory;
	int active : 1;
} processor_t;

processor_t* create_processor(void);
void free_processor(processor_t*);

word_t inc_stack(stack_t* stack);
void cycle(processor_t*);

word_t inc_stack(stack_t* stack)
{
	push_to(stack, pop_from(stack)+1);
	return peak(stack);
}

void cycle(processor_t* processor)
{
	switch (processor->memory[peak(processor->call_stack)])
	{
		case nop:
			break;

		case push:
			push_to(processor->data_stack, processor->memory[
				inc_stack(processor->call_stack)]);
			break;

		case pop:
			pop_from(processor->data_stack);
			break;
	
		case add:
			push_to(processor->data_stack,
				pop_from(processor->data_stack) +
				pop_from(processor->data_stack));
			break;

		case out:
			printf("[%d]\n", peak(processor->data_stack));
			break;

		case halt:
			processor->active = 0;
			break;

		default:
			printf("*ex.err: unrecognised opcode*\n");
	}
	inc_stack(processor->call_stack);
}

processor_t* create_processor(void)
{
	processor_t* processor = (processor_t *)malloc(sizeof(processor));
	processor->data_stack = create_stack();
	processor->call_stack = create_stack();
	processor->memory = (word_t*)malloc(MEMORYSIZE);
	processor->active = 1;
	return processor;
}

void free_processor(processor_t* processor)
{
	free_stack(processor->data_stack);
	free(processor->memory);
	free(processor);
}
