#include "TemplateMalg.h"
#include <math.h>
void TM_grayscale(unsigned char* bitmap, int width, int height)
{
	int aux;
	for(int i=0;i<width * height;i++)
	{
		aux = 0.299*bitmap[3 * i + 0] + 0.587*bitmap[3 * i+1] + 0.114*bitmap[3 * i + 2];
		bitmap[3 * i] = bitmap[3 * i + 1] = bitmap[3 * i + 2] = aux;
	}
	return;
}
int d2(int i, int j, int width)
{
	return (i * width) + j;
}
float average_template_gray_intensity(unsigned char* template, int template_width,int template_height)
{
	int i;
	float avr = 0;
	for(i=0;i<template_width*template_height;i++)
	{
		avr = avr + template[i * 3];
	}
	avr = (float)avr / (template_width*template_height);
	return avr;
}
float standard_deriv_template(unsigned char* template, int template_width, int template_height)
{
	int n, i;
	n = template_width * template_height;
	float deriv = 0;
	float sbar = average_template_gray_intensity(template, template_width, template_height);
	for (i=0; i<n; i++)
	{
		deriv += (float)(template[i * 3] - sbar) * (float)(template[i * 3] - sbar);
	}
	deriv = (float) (1 / (n + 1) * deriv);
	deriv = sqrt(deriv);
	return deriv;
}
float TM_correlation(unsigned char* bitmap, int bitmap_width, int bitmap_height, unsigned char* template, int template_width, int template_height)
{
	int n,i,j;
	float sbar,fbar;
	//int top_left_offset = d2(top_left[0], top_left[1], bitmap_width);
	sbar = average_template_gray_intensity(template, template_width, template_height);
	//fbar = average_image_gray_intensity(bitmap, template_width, template_height, top_left_offset);
	n = template_height * template_width;

	for(i=0;i<template_height;i++)
		for(j=0;j<template_width;j++)
		{
			
		}
	
}

//OUT OF ORDER
/*
 float average_image_gray_intensity(unsigned char* bitmap, int template_width, int template_height, int top_left_offset)
{
	int i;
	float avr = 0;
	for (i = 0; i < template_width*template_height; i++)
	{
		avr = avr + bitmap[top_left_offset + (i * 3)];
	}
	avr = (float)avr / (template_width*template_height);
	return avr;
}
float standard_deriv_image(unsigned char* template, int template_width, int template_height, int top_left_offset)
{
	int n, i;
	n = template_width * template_height;
	float deriv = 0;
	float sbar = average_image_gray_intensity(template, template_width, template_height, top_left_offset);
	for (i = 0; i < n; i++)
	{
		deriv += (float)(template[top_left_offset + (i * 3)] - sbar) * (float)(template[top_left_offset + (i * 3)] - sbar);
	}
	deriv = (float)(1 / (n + 1) * deriv);
	deriv = sqrt(deriv);
	return deriv;
}

 */