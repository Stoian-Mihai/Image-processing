#pragma once
#pragma once
#ifndef TemplateMalg_H_   
#define TemplateMalg_H_
#include <stdlib.h>
#include <stdio.h>
void TM_grayscale(unsigned char* bitmap, int width, int height);
void template_matching(unsigned char* bitmap, unsigned char* template, int bitmap_width, int bitmap_height, int template_width, int template_height, float mincorr);

unsigned char* cut_template(unsigned char* bitmap, int bitmap_width, int template_width, int template_height, int top_i, int top_j);
unsigned char* draw_red(unsigned char* bitmap, int bitmap_width, int template_width, int template_height, int top_i, int top_j);


#endif 