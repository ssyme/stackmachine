#include <stdio.h>
#include <stdlib.h>
#include "processor.h"

int main()
{
	processor_t *p = init_processor();

  // 0: nop,  1: push,  2: pop,   3: add
  // 4: out,  5: jump,  7: halt

	word code[] =
  {
    0x01,
    0x01,
    0x01,
    0x01,
    0x03,
    0x04,
    0x05,
    0x00,
    0x06
  };
	run(p, code, 10);

	return 0;
}