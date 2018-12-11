#pragma once
#include "bitmapalg.h"
#include "mathalgorithms.h"
char* bitmap_alg_permutation(char *bitmap,int height,int width,int size, int seed)
{
	int *p, i;
	char* bitmap_perm;
	bitmap_perm = malloc(size);
	p = random_permutation(height*width, seed);

	for(i=0;i<height*width;i++)
	{
		int pixel_curent_postion = i * 3;
		int pixel_new_postion = p[i] * 3;

		bitmap_perm[pixel_new_postion] = bitmap[pixel_curent_postion];
		bitmap_perm[pixel_new_postion+1] = bitmap[pixel_curent_postion + 1];
		bitmap_perm[pixel_new_postion+2] = bitmap[pixel_curent_postion + 2];
	}
	for (int i = 0; i < 54; i++)
	{
		bitmap_perm[height*width * 3 + i] = bitmap[height*width * 3 + i];
	}
	return bitmap_perm;
}