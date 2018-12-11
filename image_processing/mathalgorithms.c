#include "mathalgorithms.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int* xorshift32(int size, int seed)
{
	unsigned int r, k;
	r = (unsigned int) seed;
	unsigned int* v = calloc(size, sizeof(int));
	v[0] = seed;
	for(k = 1; k<=size;k++)
	{
		r = r ^ r << 13; 
		r = r ^ r >> 17;
		r = r ^ r << 5;
		v[k] = (unsigned int) r;
	}
	
	return v;
}
int* random_permutation(int size, int seed)
{
	unsigned int r = 0, aux, rand_it = 0, perm_size, rand_size, *p; 
	unsigned int *random_sequence;
	int k;
	perm_size = size;
	rand_size = 2 * size - 1;
	p = malloc(perm_size * sizeof(int));

	random_sequence = xorshift32(rand_size, seed);


	for (k = 0; k < perm_size; k++)
		p[k] = k;
	
	for (k = perm_size - 1; k >= 0; k--)
	{
		r = random_sequence[++rand_it];
		r = r % ((size)-1);
		aux = p[r];
		p[r] = p[k];
		p[k] = aux;

	}
	//free(random_sequence);
	return p;
}
