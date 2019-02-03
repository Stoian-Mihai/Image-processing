#include <stdio.h>
#include <stdlib.h>

#include "bitmapIO.h"
#include "mathalgorithms.h"
#include "bitmapalg.h"
#include "TemplateMalg.h"
void encrypt()
{
	unsigned char input_image_name[25], output_image_name[25], secret_key_name[25];
	FILE *skey;
	int seed, SV;
	

	printf("Enter input bmp image name:\n");
	scanf("%s", &input_image_name);
	printf("Enter output bmp image name:\n");
	scanf("%s", &output_image_name);
	printf("Enter secret key txt file name:\n");
	scanf("%s", &secret_key_name);

	skey = fopen(secret_key_name, "r");
	fscanf(skey,"%d%d", &seed, &SV);

	
	int bitmap_height, bitmap_width, bitmap_size;

	bitmap_height = bitmap_data_height(input_image_name);
	bitmap_width = bitmap_data_width(input_image_name);
	bitmap_size = bitmap_data_size(input_image_name);

	unsigned char* bitmap = bitmap_load(input_image_name);
	unsigned char* crypt = bitmap_alg_crypt(bitmap, bitmap_height, bitmap_width, bitmap_size, 987654321, 123456789);
	bitmap_unload(input_image_name, output_image_name, crypt);
	
	return;
}
void decrypt()
{
	unsigned char input_image_name[25], output_image_name[25], secret_key_name[25];
	FILE *skey;
	int seed, SV;


	printf("Enter input bmp image name:\n");
	scanf("%s", &input_image_name);
	printf("Enter output bmp image name:\n");
	scanf("%s", &output_image_name);
	printf("Enter secret key txt file name:\n");
	scanf("%s", &secret_key_name);

	skey = fopen(secret_key_name, "r");
	fscanf(skey, "%d%d", &seed, &SV);


	int bitmap_height, bitmap_width, bitmap_size;

	bitmap_height = bitmap_data_height(input_image_name);
	bitmap_width = bitmap_data_width(input_image_name);
	bitmap_size = bitmap_data_size(input_image_name);

	unsigned char* crypt = bitmap_load(input_image_name);
	unsigned char* bitmap = bitmap_alg_decrypt(crypt, bitmap_height, bitmap_width, bitmap_size, 987654321, 123456789);
	bitmap_unload(input_image_name, output_image_name, bitmap);

	return;
}
void t_matching()
{
	printf("Enter minimum corelation\n");
	float corr;
	int bitmap_width, bitmap_height;
	scanf("%f", &corr);
	unsigned char input_image_name[25], output_image_name[25], template_image_name[25];
	printf("Enter input bmp image name:\n");
	scanf("%s", &input_image_name);
	printf("Enter output bmp image name:\n");
	scanf("%s", &output_image_name);
	printf("Enter template bmp image name:\n");
	scanf("%s", &template_image_name);
	unsigned char *bitmap = bitmap_load(input_image_name);
	bitmap_width = bitmap_data_width(input_image_name);
	bitmap_height = bitmap_data_height(input_image_name);

	int template_width, template_height;
	unsigned char *template = bitmap_load(template_image_name);
	template_width = bitmap_data_width(template_image_name);
	template_height = bitmap_data_height(template_image_name);

	template_matching(bitmap,template, bitmap_width, bitmap_height, template_width,template_height,corr);

	bitmap_unload(input_image_name, output_image_name, bitmap);
}
void chi()
{
	unsigned char input_image_name[25];
	printf("Enter input bmp image name:\n");
	scanf("%s", &input_image_name);
	chi_test(input_image_name);
}
int main()
{
	
	printf("Choose:\n");
	printf("1. encrypt image\n");
	printf("2. decrypt image\n");
	printf("3. chy test\n");
	printf("4. apply template matching\n");
	int option;
	scanf("%d", &option);
	switch (option) {

	case 1:
		encrypt();
		break; 

	case 2:
		decrypt();
		break;
	case 3:
		chi();
		break;
	case 4:
		t_matching();
		break;
		
	}
	
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
