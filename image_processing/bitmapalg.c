#pragma once
#include "bitmapalg.h"
#include "mathalgorithms.h"
#include "bitmapIO.h"
#include <stdio.h>

union split_integer
{
	unsigned int i;
	char s[4];
};
unsigned char* bitmap_alg_permutation(unsigned char *bitmap,int height,int width,int size, int seed, int *permutation)
{
	int *p, i;
	p = permutation;
	unsigned char* bitmap_perm;
	bitmap_perm = malloc(size);
	

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
unsigned char* bitmap_xor(unsigned char *bitmap,int height,int width,int seed, unsigned int SV)
{
	int i;
	unsigned int* random_sequence;
	random_sequence = xorshift32((2*height*width)-1, seed);
	union split_integer x,y;
	x.i = SV;
	y.i = random_sequence[width*height];
	bitmap[0] = x.s[1] ^ bitmap[0] ^ y.s[1];
	bitmap[1] = x.s[2] ^ bitmap[1] ^ y.s[2];
	bitmap[2] = x.s[3] ^ bitmap[2] ^ y.s[3];
	

	for(i=1; i<width*height; i++)
	{
		int c_pos, prev_pos;
		c_pos = i * 3;
		prev_pos = (i - 1) * 3;
		union split_integer x;
		x.i = random_sequence[width*height + i];
		bitmap[c_pos + 0] = bitmap[prev_pos + 0] ^ bitmap[c_pos + 0] ^ x.s[1];
		bitmap[c_pos + 1] = bitmap[prev_pos + 1] ^ bitmap[c_pos + 1] ^ x.s[2];
		bitmap[c_pos + 2] = bitmap[prev_pos + 2] ^ bitmap[c_pos + 2] ^ x.s[3];
	}
	

	//bitmap[1] = 255;

	return bitmap;
}
unsigned char* bitmap_alg_crypt(unsigned char *bitmap, int height, int width, int size,int seed, unsigned int SV)
{
	height = bitmap_data_height("test.bmp");
	width = bitmap_data_width("test.bmp");
	size = bitmap_data_size("test.bmp");
	int *Rpermutation,*permutated_bitmap, *crypted_bitmap;

	Rpermutation = random_permutation(height*width, seed);
	permutated_bitmap = bitmap_alg_permutation(bitmap, height, width, size, seed, Rpermutation);
	crypted_bitmap = bitmap_xor(permutated_bitmap, height, width, seed, SV);

	return crypted_bitmap;

}