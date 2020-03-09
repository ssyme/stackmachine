#include <stdlib.h>
#include "stack.h"

typedef struct
{
	word status, immediate, *memory; // status: r r r ofl zro pos jmp halt
	stack_t *dst, *cst; // data stack and call stack
} processor_t;

processor_t* init_processor(void);
void run(processor_t*, word*, int);
void incpc(processor_t*);

void nop(processor_t*);
void push(processor_t*);
void pop(processor_t*);
void add(processor_t*);
void out(processor_t*);
void jump(processor_t*);
void halt(processor_t*);

void (*opcodes[])(processor_t*) =
{
	&nop,
	&push,
	&pop,
	&add,
	&out,
	&jump,
	&halt
};

processor_t* init_processor(void)
{
	processor_t *processor = malloc(sizeof *processor);
	processor->status = 0;
	processor->memory = malloc(sizeof(word)*256);
	processor->dst = init_stack(15);
	processor->cst = init_stack(15);
	return processor;
}

void run(processor_t* processor, word* code, int codelen)
{
	word nextinst;
	for (int i = 0; i < codelen; i++)
	{
		processor->memory[i] = code[i];
	}
	while (~processor->status&1)
	{
		nextinst = processor->memory[peak_stack(processor->cst)];
		processor->immediate = processor->memory[
			peak_stack(processor->cst)+1];
		opcodes[nextinst](processor);
		incpc(processor);
	}
}

void incpc(processor_t* processor)
{
	push_to_stack(processor->cst, 1);
	push_to_stack(processor->cst,
		pop_stack(processor->cst) + pop_stack(processor->cst));
}

void nop(processor_t* processor)
{
}

void push(processor_t* processor)
{
	push_to_stack(processor->dst, processor->immediate);
	incpc(processor);
}

void pop(processor_t* processor)
{
	pop_stack(processor->dst);
}

void add(processor_t* processor)
{
	word r = pop_stack(processor->dst) + pop_stack(processor->dst);
	push_to_stack(processor->dst, r);
}

void out(processor_t* processor)
{
	printf("%d\n", peak_stack(processor->dst));
}

void jump(processor_t* processor)
{
	push_to_stack(processor->cst, processor->immediate);
	incpc(processor);
}

void halt(processor_t* processor)
{
	processor->status |= 1;
}
