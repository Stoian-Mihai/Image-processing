#include "algorithms.h"
#include <stdio.h>

int xorshift32()
{
	unsigned int r, k, seed = 1000;
	r = seed;

	for(k = 0; k<10;k++)
	{
		r = r ^ r << 13;
		r = r ^ r >> 17;
		r = r ^ r << 5;
		printf("%u\n", r);
	}
}
