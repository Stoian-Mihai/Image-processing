#include <stdio.h>
#include <stdlib.h>
//#include "image_draw.h"
#include "bitmap.h"
#include "algorithms.h"
int main()
{
	char color[3];
	color[0] = 0;
	color[1] = 255;
	color[2] = 0;
	int pixel[2];
	pixel[0] = 499;
	pixel[1] = 0;
	//bitmap_draw_pixel("test.bmp", pixel, color);
	int height, width, size;
	height = bitmap_height("test.bmp");
	width = bitmap_width("test.bmp");
	size = bitmap_size("test.bmp");
	char *v = bitmap_load("test.bmp");
	char *p = bitmap_flip(v, width, height, size);
    char *c = bitmap_unflip(p, width, height, size);
	bitmap_unload("print2.bmp", c, size);
	
	/*
	//int off = pixel_to_pos(pixel, height, width);
	//printf("%d", off);
	
	//char *v = bitmap_load("test.bmp");
	//printf("%d",sizeof(v));
	//int size = bitmap_size("test.bmp");
	//bitmap_unload("print.bmp", v, size);
	//unsigned int *v;
	//v = xorshift32(400);*/
	

	system("pause"); 
	return 0;

}