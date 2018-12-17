#pragma once
#ifndef bitmapalg_H__H_   
#define bitmapalg_H_
#include <stdlib.h>

unsigned char* bitmap_alg_crypt(unsigned char *bitmap, int height, int width, int size, int seed, unsigned int SV);
unsigned char* bitmap_alg_decrypt(unsigned char *crypted_bitmap, int height, int width, int size, int seed, unsigned int SV);
#endif 
//OUT OF ORDER
/*
 unsigned char* bitmap_inverse_xor(unsigned char *bitmap, int height, int width, int seed, unsigned int SV);
 unsigned char* bitmap_xor(unsigned char *bitmap, int height, int width, int seed, unsigned int SV);
 unsigned char* bitmap_alg_permutation(unsigned char *bitmap, int height, int width, int size, int seed, int *permutation);
 */