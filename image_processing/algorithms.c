#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int* xorshift32(int size)
{
	unsigned int r, k, seed = 1000;
	r = seed;
	unsigned int* v = calloc(size, sizeof(int));
	for(k = 0; k<size;k++)
	{
		r = r ^ r << 13; 
		r = r ^ r >> 17;
		r = r ^ r << 5;
		v[k] = (unsigned int) r;
	}
	return v;
}
