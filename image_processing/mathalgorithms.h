#pragma once
#ifndef algorithms_H_   
#define algorithms_H_
#include <stdlib.h>
int* random_permutation(int size, int seed);
unsigned int* xorshift32(int size, int seed);
int*  inverse_permutation(int* permutation, int size);
#endif 