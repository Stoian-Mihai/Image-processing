#include <stdio.h>
#include <stdlib.h>
//#include "image_draw.h"
#include "bitmap.h"
int main()
{
	/*point  c;
	c.x = 10;
	c.y = 4;
	draw_line("caca.bmp", c, c);
	*/
	char color[3];
	color[0] = 0;
	color[1] = 255;
	color[2] = 0;
	int pixel[2];
	pixel[0] = 483;
	pixel[1] = 51;
	bitmap_draw_pixel("test.bmp", pixel, color);
	system("pause"); //Fixing Visual studio shit
	return 0;

}