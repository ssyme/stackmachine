#include <stdio.h>
#include <stdlib.h>
#include "processor.h"

int main()
{
	processor_t *p = init_processor();

	word code[] = {0x01, 0x01, 0x01, 0x01, 0x03, 0x04, 0x05, 0x00};
	run(p, code, 8);

	return 0;
}
