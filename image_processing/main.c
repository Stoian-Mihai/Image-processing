#include <stdio.h>
#include <stdlib.h>

#include "bitmapIO.h"
#include "algorithms.h"
int main()
{
	
	

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
	char *v = bitmap_load("test.bmp");
	char *p = bitmap_linearize(v, width, height, size);
    char *c = bitmap_unlinearize(p, width, height, size);
	bitmap_unload("print2.bmp", c, size);
var2
    char *v = bitmap_load("test.bmp");
	bitmap_unload("test.bmp", "new.bmp", v);
-------------------

 */