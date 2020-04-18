#ifndef SPEC_H
#define SPEC_H

#define MEMORYSIZE 256

typedef char word_t;

enum instruction_set {
	nop,							// 0
	push,							// 1
	pop,							// 2
	add,							// 3
	out,							// 4
	halt							// 5
};
#endif
