#include <stdio.h>
#include <stdlib.h>

#include "bitmapIO.h"
#include "mathalgorithms.h"
#include "bitmapalg.h"
#include "TemplateMalg.h"
int main()
{
	
	int bitmap_height, bitmap_width, bitmap_size, seed;
	unsigned int SV;
	bitmap_height = bitmap_data_height("test.bmp");
	bitmap_width = bitmap_data_width("test.bmp");
	bitmap_size = bitmap_data_size("test.bmp");
	seed = 987654321;
	SV = 123456789;

	unsigned char *bitmap;
	bitmap = bitmap_load("test.bmp");
	unsigned char *template;
	template = bitmap_load("cifra0.bmp");
	int template_height, template_width;
	template_height = bitmap_data_height("cifra0.bmp");
	template_width = bitmap_data_width("cifra0.bmp");

	template_matching(bitmap, template, bitmap_width, bitmap_height, template_width, template_height);
	
	
	
	bitmap_unload("test.bmp", "new.bmp", bitmap);

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
-----------------------------------------------------------------
**test for permutation
	int *perm = random_permutation(5, 968574);
		for (int i = 0; i < 5; i++)
			printf("%d ", perm[i]);

**test for crypting
	int height, width, size,seed;
	seed = 987654321;
	int SV = 123456789;
	height = bitmap_data_height("test.bmp");
	width = bitmap_data_width("test.bmp");
	size = bitmap_data_size("test.bmp");
	unsigned char *v = bitmap_load("test.bmp");
	int *perm;
	perm = random_permutation(height*width, seed);
	unsigned char *p = bitmap_alg_permutation(v, height, width, size, seed, perm);

	unsigned char *cript = bitmap_xor(p, height, width, seed, SV);

	bitmap_unload("test.bmp", "new.bmp", cript);
crypting v2
	unsigned char *bitmap = bitmap_load("test.bmp");
	unsigned char *cript = bitmap_alg_crypt(bitmap, height, width, size, 987654321, 123456789);
	bitmap_unload("test.bmp", "new.bmp", cript);
---------------------------------------
test for inverse permutation
//unsigned char *v = bitmap_load("test.bmp");
	int *permutation = random_permutation(height*width, 987654321);
	//unsigned char* perm_bitmap = bitmap_alg_permutation(v, height, width, size, 987654321, permutation);
	//bitmap_unload("test.bmp", "new.bmp", perm_bitmap);
	int *inv_permutation = inverse_permutation(permutation, height*width);
	unsigned char *perm_bitmap = bitmap_load("new.bmp");
	unsigned char *v = bitmap_alg_permutation(perm_bitmap, height, width, size, 987654321, inv_permutation);
	bitmap_unload("new.bmp", "decript.bmp", v);
------------------------------------
test for decrypting
seed = 987654321;
	SV = 123456789;
	unsigned char *v = bitmap_load("test.bmp");
	unsigned char *c;
	//c = bitmap_alg_crypt(v, height, width, size, seed, SV);
	c = bitmap_alg_decrypt(v, height, width, size, seed, SV);
-------------------------------------------
 */
