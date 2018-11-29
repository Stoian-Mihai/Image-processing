#pragma once
#ifndef bitmap_H_   
#define bitmap_H_

#include <stdio.h>

//Data

//Functions
int bitmap_width(char* bitmap_name);
int bitmap_height(char* bitmap_name);
int bitmap_write_pos(char* bitmap_name, int pos, char* color);
int bitmap_draw_pixel(char* bitmap_name, int* pixel, char* color);
int pixel_to_pos(int* pixel, int height, int width);
#endif 
