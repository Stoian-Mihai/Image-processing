#pragma once
#ifndef bitmapIO_H_   
#define bitmapIO_H_

#include <stdio.h>

//Data

//Functions
char* bitmap_load(char* bitmap_name);
void bitmap_unload(char* old_bitmap_name, char* bitmap_name, char* bitmap);
int bitmap_data_height(char* bitmap_name);
int bitmap_data_width(char* bitmap_name);
int bitmap_data_size(char* bitmap_name);
#endif 

///out of order
/*
 void bitmap_write_pos(char* bitmap_name, int pos, char* color);
 int bitmap_draw_pixel(char* bitmap_name, int* pixel, char* color);
 */