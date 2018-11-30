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
	pixel[1] = 345;
	//bitmap_draw_pixel("test.bmp", pixel, color);
	//char *v = bitmap_load("test.bmp");
	//printf("%d",sizeof(v));
	//int size = bitmap_size("test.bmp");
	//bitmap_unload("print.bmp", v, size);
	xorshift32();
	system("pause"); 
	return 0;

}