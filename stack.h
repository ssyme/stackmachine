#include <stdio.h>
#include <stdlib.h>
#include "spec.h"

#define STACKDEPTH 15

typedef struct stack
{
	word_t* data;
	word_t sp;
} stack_t;

stack_t* create_stack(void);
void free_stack(stack_t*);

void push_to(stack_t*, word_t op);
word_t pop_from(stack_t*);
word_t peak(stack_t*);

stack_t* create_stack(void)
{
	stack_t* stack = (stack_t *)malloc(sizeof(stack));
	stack->data = (word_t *)malloc(STACKDEPTH);
	stack->sp = -1;
	return stack;
}

void free_stack(stack_t* stack)
{
	free(stack->data);
	free(stack);
}

void push_to(stack_t* stack, word_t op)
{
	stack->data[++stack->sp] = op;
}

word_t pop_from(stack_t* stack)
{
	return stack->sp < 0 ? 0 : stack->data[stack->sp--];
}

word_t peak(stack_t* stack)
{
	return stack->data[stack->sp];
}
