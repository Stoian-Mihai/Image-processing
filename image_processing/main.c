#include <stdio.h>
#include <stdlib.h>
//#include "image_draw.h"
#include "bitmap.h"
int main()
{
	char color[3];
	color[0] = 0;
	color[1] = 255;
	color[2] = 0;
	int pixel[2];
	pixel[0] = 499;
	pixel[1] = 345;
	bitmap_draw_pixel("test.bmp", pixel, color);
	system("pause"); //Fixing Visual studio shit
	return 0;

}