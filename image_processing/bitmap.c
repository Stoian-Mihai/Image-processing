#include "bitmap.h"
#include <stdlib.h>

/// pulling data from bitmap  functions
int bitmap_data_width(char* bitmap_name)
{
	FILE *f;
	int width = 0;

	f = fopen(bitmap_name, "rb");
	fseek(f, 18, SEEK_SET);
	fread(&width, sizeof(int), 1, f);
	return width;
}
int bitmap_data_height(char* bitmap_name)
{
	FILE *f;
	int height = 0;

	f = fopen(bitmap_name, "rb");
	fseek(f, 22, SEEK_SET);
	fread(&height, sizeof(int), 1, f);
	return height;
}
int bitmap_data_size(char* bitmap_name)
{
	FILE *f;
	int size = 0;
	f = fopen(bitmap_name, "rb");
	fseek(f, 2, SEEK_SET);
	fread(&size, sizeof(int), 1, f);
	return size;
}
/// math
int pixel_to_pos(int* pixel, int height, int width)
{
	int offset = pixel[0] + 1 + (height - pixel[1] - 1) * width;
	return offset;
}
/// loading a bitmap to memory and unloading it 
char* bitmap_load(char* bitmap_name)
{
	int size = bitmap_data_size(bitmap_name);
	char *bitmap;
	bitmap = malloc(size);
	FILE *f;	
	f = fopen(bitmap_name, "r+b");
	fread(bitmap, size, 1, f);
	return bitmap;

}
void  bitmap_unload(char* bitmap_name, char* bitmap, int size)
{
	FILE *f;
	f = fopen(bitmap_name, "w+b");
	fwrite(bitmap, sizeof(char), size, f);
}
char* bitmap_linearize(char* bitmap, int width, int height, int size)
{
	char* flipped_bitmap;
	int k = 0;

	flipped_bitmap = malloc(size);
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			int pixel[2];
			pixel[0] = j;
			pixel[1] = i;
			flipped_bitmap[k++] = bitmap[51 + pixel_to_pos(pixel, height, width)*3 + 0];
			flipped_bitmap[k++] = bitmap[51 + pixel_to_pos(pixel, height, width)*3 + 1];
			flipped_bitmap[k++] = bitmap[51 + pixel_to_pos(pixel, height, width)*3 + 2];
		}
	}

	for(int i=0;i<54;i++)
	{
		flipped_bitmap[height*width*3 + i] = bitmap[i];
	}
	free(bitmap);
	return flipped_bitmap;
}
char* bitmap_unlinearize(char* flipped_bitmap, int width, int height, int size)
{
	char* bitmap;	
	int k = 0, offset;

	bitmap = malloc(size);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int pixel[2];
			pixel[0] = j;
			pixel[1] = i;
			offset = pixel_to_pos(pixel, height, width);
			bitmap[51 + offset*3 + 0] = flipped_bitmap[k++];
			bitmap[51 + offset*3 + 1] = flipped_bitmap[k++];	
			bitmap[51 + offset*3 + 2] = flipped_bitmap[k++];
		}
	}
	for (int i = 0; i < 54; i++)
	{
		bitmap[i] = flipped_bitmap[height*width*3 + i];
	}
	free(flipped_bitmap);
	return bitmap;
}

///out of  order functions
/*
void bitmap_write_pos(char* bitmap_name, int pos, char* color)
{
	FILE *f;

	f = fopen(bitmap_name, "r+b");
	fseek(f, 51 + pos * 3, SEEK_SET);
	fwrite(color, 3, 1, f);


}
int bitmap_draw_pixel(char* bitmap_name, int* pixel, char* color)
{
	int width = bitmap_data_width(bitmap_name);
	int height = bitmap_data_height(bitmap_name);
	int offset = pixel_to_pos(pixel, height, width);
	bitmap_write_pos("test.bmp", offset, color);


}
*/