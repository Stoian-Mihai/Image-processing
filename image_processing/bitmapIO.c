#include "bitmapIO.h"
#include <stdlib.h>

/// pulling data from bitmap  functions
int bitmap_data_width(unsigned char* bitmap_name)
{
	FILE *f;
	int width = 0;

	f = fopen(bitmap_name, "rb");
	fseek(f, 18, SEEK_SET);
	fread(&width, sizeof(int), 1, f);
	return width;
}
int bitmap_data_height(unsigned char* bitmap_name)
{
	FILE *f;
	int height = 0;

	f = fopen(bitmap_name, "rb");
	fseek(f, 22, SEEK_SET);
	fread(&height, sizeof(int), 1, f);
	return height;
}
int bitmap_data_size(unsigned char* bitmap_name)
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
unsigned char* bitmap_linearize(unsigned char* bitmap, int width, int height, int size)
{
	unsigned char* flipped_bitmap;
	int k = 0;

	flipped_bitmap = malloc(size);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int pixel[2];
			pixel[0] = j;
			pixel[1] = i;
			flipped_bitmap[k++] = bitmap[51 + pixel_to_pos(pixel, height, width) * 3 + 0];
			flipped_bitmap[k++] = bitmap[51 + pixel_to_pos(pixel, height, width) * 3 + 1];
			flipped_bitmap[k++] = bitmap[51 + pixel_to_pos(pixel, height, width) * 3 + 2];

			unsigned char aux;
			aux = flipped_bitmap[k - 1];
			flipped_bitmap[k - 1] = flipped_bitmap[k - 3];
			flipped_bitmap[k - 3] = aux;
		}
	}

	for (int i = 0; i < 54; i++)
	{
		flipped_bitmap[height*width * 3 + i] = bitmap[i];
	}
	free(bitmap);
	return flipped_bitmap;
}
unsigned char* bitmap_unlinearize(unsigned char* flipped_bitmap, int width, int height, int size)
{
	unsigned char* bitmap;
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
			bitmap[51 + offset * 3 + 0] = flipped_bitmap[k++];
			bitmap[51 + offset * 3 + 1] = flipped_bitmap[k++];
			bitmap[51 + offset * 3 + 2] = flipped_bitmap[k++];

			unsigned char aux;
			aux = bitmap[51 + offset * 3 + 0];
			bitmap[51 + offset * 3 + 0] = bitmap[51 + offset * 3 + 2];
			bitmap[51 + offset * 3 + 2] = aux;
		}
	}
	for (int i = 0; i < 54; i++)
	{
		bitmap[i] = flipped_bitmap[height*width * 3 + i];
	}
	free(flipped_bitmap);
	return bitmap;
}
unsigned char* bitmap_load(unsigned char* bitmap_name)
{
	int size, height, width;
	unsigned char *bitmap, *flipped_bitmap;

	size = bitmap_data_size(bitmap_name);
	height = bitmap_data_height(bitmap_name);
	width = bitmap_data_width(bitmap_name);
	bitmap = malloc(size);

	FILE *f;	
	f = fopen(bitmap_name, "r+b");
	fread(bitmap, size, 1, f);
	flipped_bitmap = bitmap_linearize(bitmap, width, height, size);
	
	return flipped_bitmap;

}
void  bitmap_unload(unsigned char* old_bitmap_name, unsigned char* bitmap_name, unsigned char* bitmap)
{
	int size, height, width;
	unsigned char *flipped_bitmap;

	size = bitmap_data_size(old_bitmap_name);
	height = bitmap_data_height(old_bitmap_name);
	width = bitmap_data_width(old_bitmap_name);
	flipped_bitmap = bitmap_unlinearize(bitmap, width, height, size);

	FILE *f;
	f = fopen(bitmap_name, "w+b");
	fwrite(flipped_bitmap, sizeof(unsigned char), size, f);
}


///out of  order functions
/*
void bitmap_write_pos(unsigned char* bitmap_name, int pos, unsigned char* color)
{
	FILE *f;

	f = fopen(bitmap_name, "r+b");
	fseek(f, 51 + pos * 3, SEEK_SET);
	fwrite(color, 3, 1, f);


}
int bitmap_draw_pixel(unsigned char* bitmap_name, int* pixel, unsigned char* color)
{
	int width = bitmap_data_width(bitmap_name);
	int height = bitmap_data_height(bitmap_name);
	int offset = pixel_to_pos(pixel, height, width);
	bitmap_write_pos("test.bmp", offset, color);


}
*/