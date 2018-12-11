#pragma once
#ifndef bitmapalg_H__H_   
#define bitmapalg_H_
#include <stdlib.h>

unsigned char* bitmap_alg_permutation(unsigned char *bitmap, int height, int width, int size, int seed);
unsigned char* bitmap_xor(unsigned char *bitmap, int height, int width, int seed, unsigned int SV);
#endif 