#include <stdio.h>
#include <stdlib.h>

#include "bitmapIO.h"
#include "mathalgorithms.h"
#include "bitmapalg.h"
int main()
{
	
	
	int height, width, size,seed;
	seed = 987654321;
	int SV = 123456789;
	height = bitmap_data_height("test.bmp");
	width = bitmap_data_width("test.bmp");
	size = bitmap_data_size("test.bmp");
	unsigned char *v = bitmap_load("test.bmp");
	unsigned char *p = bitmap_alg_permutation(v, height, width, size, seed);
	
	unsigned char *cript = bitmap_xor(p, height, width, seed, SV);
	
	bitmap_unload("test.bmp", "new.bmp", cript);
	
	
	system("pause"); 
	return 0;

}

/// debug and tests
/*
 **test for bitmap_load / bitmap_linearize / bitmap_unlinearize / bitmap_unload
-----------------
int pixel[2];
	pixel[0] = 0;
	pixel[1] = 0;
	int height, width, size;
	height = bitmap_data_height("test.bmp"); // 400
	width = bitmap_data_width("test.bmp"); // 500
	size = bitmap_data_size("test.bmp");
	unsigned char *v = bitmap_load("test.bmp");
	unsigned char *p = bitmap_linearize(v, width, height, size);
	unsigned char *c = bitmap_unlinearize(p, width, height, size);
	bitmap_unload("print2.bmp", c, size);
var2
	unsigned char *v = bitmap_load("test.bmp");
	bitmap_unload("test.bmp", "new.bmp", v);
-------------------

 */