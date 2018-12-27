#pragma once
#include "bitmapalg.h"
#include "mathalgorithms.h"
#include "bitmapIO.h"
#include <stdio.h>

union split_integer
{
	unsigned int i;
	unsigned char s[4];
};
unsigned char* bitmap_alg_permutation(unsigned char *bitmap,int height,int width,int size, int seed, int *permutation)
{
	int *p, i;
	p = permutation;
	unsigned char* bitmap_perm;
	bitmap_perm = malloc(size+1);
	

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
	free(bitmap);
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
	

	
	free(random_sequence);
	return bitmap;
}
unsigned char* bitmap_inverse_xor(unsigned char *bitmap, int height, int width, int seed, unsigned int SV)
{
	int i;
	unsigned int* random_sequence;
	random_sequence = xorshift32((2 * height*width) - 1, seed);
	union split_integer x, y;
	x.i = SV;
	y.i = random_sequence[width*height];
	unsigned char prev_byte0, prev_byte1, prev_byte2, aux;
	prev_byte0 = bitmap[0]; prev_byte1 = bitmap[1]; prev_byte2 = bitmap[2];
	bitmap[0] = x.s[1] ^ bitmap[0] ^ y.s[1];
	bitmap[1] = x.s[2] ^ bitmap[1] ^ y.s[2];
	bitmap[2] = x.s[3] ^ bitmap[2] ^ y.s[3];
	
	
	for (i = 1; i < width*height; i++)
	{

		int c_pos, prev_pos;
		c_pos = i * 3;
		prev_pos = (i - 1) * 3;
		union split_integer x;
		x.i = random_sequence[width*height + i];
		aux = bitmap[c_pos + 0];
		bitmap[c_pos + 0] = prev_byte0 ^ bitmap[c_pos + 0] ^ x.s[1];
		prev_byte0 = aux;
		aux = bitmap[c_pos + 1];
		bitmap[c_pos + 1] = prev_byte1 ^ bitmap[c_pos + 1] ^ x.s[2];
		prev_byte1 = aux;
		aux = bitmap[c_pos + 2];
		bitmap[c_pos + 2] = prev_byte2 ^ bitmap[c_pos + 2] ^ x.s[3];
		prev_byte2 = aux;


	}



	free(random_sequence);
	return bitmap;
}
unsigned char* bitmap_alg_crypt(unsigned char *bitmap, int height, int width, int size,int seed, unsigned int SV)
{
	
	int *Rpermutation,*permutated_bitmap, *crypted_bitmap;

	Rpermutation = random_permutation(height*width, seed);
	permutated_bitmap = bitmap_alg_permutation(bitmap, height, width, size, seed, Rpermutation);
	crypted_bitmap = bitmap_xor(permutated_bitmap, height, width, seed, SV);
	free(Rpermutation);
	return crypted_bitmap;

}
unsigned char* bitmap_alg_decrypt(unsigned char *crypted_bitmap, int height, int width, int size, int seed, unsigned int SV)
{
	int *Rpermutation, *permutated_bitmap, *bitmap, *Inverse_permutation;

	bitmap = bitmap_inverse_xor(crypted_bitmap, height, width, seed, SV);
	Rpermutation = random_permutation(width*height, seed);
	Inverse_permutation = inverse_permutation(Rpermutation, width*height);
	permutated_bitmap = bitmap_alg_permutation(bitmap, height, width, size, seed, Inverse_permutation);
	free(Inverse_permutation);
	return permutated_bitmap;
}
float* chi_test(unsigned char* bitmap_name)
{
	int size, height, width;
	unsigned char *bitmap = bitmap_load(bitmap_name);
	size = bitmap_data_size(bitmap_name);
	height = bitmap_data_height(bitmap_name);
	width = bitmap_data_width(bitmap_name);
	
	float *chi;
	chi = calloc(4, sizeof(float));
	for (int i = 0; i <= 255; i++)
	{
		int fiR, fiG, fiB;
		fiR = fiG = fiB = 0;
		for (int j = 0; j < width*height; j++)
		{
			int R, G, B;
			R = j * 3;
			G = R + 1;
			B = R + 2;

			if (bitmap[R] == i) fiR++;
			if (bitmap[G] == i) fiG++;
			if (bitmap[B] == i) fiB++;
		}
		float fbar = (width * height) / 256;
		chi[0] += ((fiR - fbar) * (fiR - fbar)) / fbar;
		chi[1] += ((fiG - fbar) * (fiG - fbar)) / fbar;
		chi[2] += ((fiB - fbar) * (fiB - fbar)) / fbar;
	}
	printf(" chiR: %f\n chiG: %f\n chiB: %f\n",chi[0],chi[1],chi[2]);
	return chi;
}