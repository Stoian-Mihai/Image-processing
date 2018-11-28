#pragma once
#ifndef image_draw_H_   
#define image_draw_H_

#include <stdio.h>

//Data
typedef struct{
	int x;
	int y;
} point;

//Functions
void draw_line(char image_name,  point a, point b);
void draw_pixel(char image_name, point a);
#endif 
