#include "bitmap.h"

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
int bitmap_write_pos(char* bitmap_name, int pos, char* color)
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
	int offset = pixel[0] + pixel[1] * width;
	//offset = height * width - offset;
	
	bitmap_write_pos("test.bmp",200000, color);
	
}