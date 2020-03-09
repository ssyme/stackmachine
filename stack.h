#include <stdio.h>
#include <stdlib.h>

typedef char word;

typedef struct
{
	word sp, *data;
} stack_t;

stack_t* init_stack(int);
void push_to_stack(stack_t*, word);
word peak_stack(stack_t*);
word pop_stack(stack_t*);

stack_t* init_stack(int size)
{
	stack_t *stack = malloc(sizeof *stack);
	stack->sp = 0;
	stack->data = malloc(sizeof(word)*size);
	return stack;
}

void push_to_stack(stack_t *stack, word operand)
{
	stack->data[++stack->sp] = operand;
}

word peak_stack(stack_t *stack)
{
	return stack->data[stack->sp];
}

word pop_stack(stack_t *stack)
{
	word top = peak_stack(stack);
	stack->sp--;
	return top;
}
