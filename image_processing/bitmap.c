#include "bitmap.h"
#include <stdlib.h>

int bitmap_width(char* bitmap_name)
{
	FILE *f;
	int width = 0;

	f = fopen(bitmap_name, "rb");
	fseek(f, 18, SEEK_SET);
	fread(&width, sizeof(int), 1, f);
	return width;
}
int bitmap_height(char* bitmap_name)
{
	FILE *f;
	int height = 0;

	f = fopen(bitmap_name, "rb");
	fseek(f, 22, SEEK_SET);
	fread(&height, sizeof(int), 1, f);
	return height;
}
int bitmap_size(char* bitmap_name)
{
	FILE *f;
	int size = 0;
	f = fopen(bitmap_name, "rb");
	fseek(f, 2, SEEK_SET);
	fread(&size, sizeof(int), 1, f);
	return size;
}
void bitmap_write_pos(char* bitmap_name, int pos, char* color)
{
	FILE *f;

	f = fopen(bitmap_name, "r+b");
	fseek(f, 51 + pos*3, SEEK_SET);
	fwrite(color, 3, 1, f);
	
	
}
int bitmap_draw_pixel(char* bitmap_name, int* pixel, char* color)
{
	int width = bitmap_width(bitmap_name);
	int height = bitmap_height(bitmap_name);
	int offset = pixel_to_pos(pixel, height, width);
	printf("%d\n", offset);
	bitmap_write_pos("test.bmp",offset, color);
	
}
int pixel_to_pos(int* pixel, int height, int width)
{
	int offset = pixel[0] + 1 + (height - pixel[1] - 1) * width;
	return offset;
}
char* bitmap_load(char* bitmap_name)
{
	int size = bitmap_size(bitmap_name);
	char *v;
	v = malloc(size);
	FILE *f;	
	f = fopen(bitmap_name, "r+b");
	fread(v, size, 1, f);
	return v;

}
void bitmap_unload(char* bitmap_name, char* v, int size)
{
	FILE *f;
	f = fopen(bitmap_name, "w+b");
	fwrite(v, sizeof(char), size, f);
}
char* bitmap_flip(char* bitmap, int width, int height, int size)
{
	char* flipped_bitmap;
	flipped_bitmap = malloc(size);
	int k = 0;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			int pixel[2];
			pixel[0] = j;
			pixel[1] = i;
			flipped_bitmap[k++] = bitmap[pixel_to_pos(pixel, height, width)*3 + 0];
			flipped_bitmap[k++] = bitmap[pixel_to_pos(pixel, height, width)*3 + 1];
			flipped_bitmap[k++] = bitmap[pixel_to_pos(pixel, height, width)*3 + 2];
		}
	}
	free(bitmap);
	return flipped_bitmap;
}
char* bitmap_unflip(char* flipped_bitmap, int width, int height, int size)
{
	char* bitmap;
	bitmap = malloc(size);
	int k = 0, offset;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int pixel[2];
			pixel[0] = j;
			pixel[1] = i;
			if(k == 460932)
			{
				printf("cacat");
			}
			offset = pixel_to_pos(pixel, height, width);
			bitmap[offset*3 + 0] = flipped_bitmap[k++];
			bitmap[offset*3 + 1] = flipped_bitmap[k++];	
			bitmap[offset*3 + 2] = flipped_bitmap[k++];
		}
	}
	printf("%d", bitmap[460932]);
	free(flipped_bitmap);
	return bitmap;
}
