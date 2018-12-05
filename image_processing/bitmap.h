#pragma once
#ifndef bitmap_H_   
#define bitmap_H_

#include <stdio.h>

//Data

//Functions
int bitmap_data_width(char* bitmap_name);
int bitmap_data_height(char* bitmap_name);
int bitmap_data_size(char* bitmap_name);
int pixel_to_pos(int* pixel, int height, int width);
char* bitmap_load(char* bitmap_name);
void bitmap_unload(char* old_bitmap_name, char* bitmap_name, char* bitmap);
char* bitmap_linearize(char* bitmap, int width, int height, int size);
char* bitmap_unlinearize(char* flipped_bitmap, int width, int height, int size);
#endif 

///out of order
/*
 void bitmap_write_pos(char* bitmap_name, int pos, char* color);
 int bitmap_draw_pixel(char* bitmap_name, int* pixel, char* color);
 */