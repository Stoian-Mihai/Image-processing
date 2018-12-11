#pragma once
#ifndef bitmapIO_H_   
#define bitmapIO_H_

#include <stdio.h>

//Data

//Functions
unsigned char* bitmap_load(unsigned char* bitmap_name);
void bitmap_unload(unsigned char* old_bitmap_name, unsigned char* bitmap_name, unsigned char* bitmap);
int bitmap_data_height(unsigned char* bitmap_name);
int bitmap_data_width(unsigned char* bitmap_name);
int bitmap_data_size(unsigned char* bitmap_name);
#endif 

///out of order
/*
 void bitmap_write_pos(unsigned char* bitmap_name, int pos, unsigned char* color);
 int bitmap_draw_pixel(unsigned char* bitmap_name, int* pixel, unsigned char* color);
 */