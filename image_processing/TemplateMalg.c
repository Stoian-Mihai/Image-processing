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
unsigned char* cut_template(unsigned char* bitmap, int bitmap_width, int template_width, int template_height, int top_i, int top_j)
{
	unsigned char *cuted_template = malloc((3 *template_width * template_height) + 60);
	int i, j, k=0;

	for (i = top_i; i < template_width + top_i; i++)
	{
		for (j = top_j; j < template_height + top_j; j++)
		{
			int offset = d2(i, j, bitmap_width);
			cuted_template[k++] = bitmap[3 * offset + 0];
			cuted_template[k++] = bitmap[3 * offset + 1];
			cuted_template[k++] = bitmap[3 * offset + 2];
			//printf("(%u, %u, %u)", cuted_template[k - 3], cuted_template[k - 2], cuted_template[k - 1]);
		}
		//printf("\n");
	}
	return cuted_template;
}
float average_template_gray_intensity(unsigned char* template, int template_width, int template_height)
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
		deriv += (float)((float)template[i * 3] - sbar) * ((float)template[i * 3] - sbar);
	}
	deriv = (float) ((float) deriv / (n - 1));
	deriv = sqrt(deriv);
	return deriv;
}
float TM_correlation(unsigned char* cuted_bitmap, unsigned char* template, int template_width, int template_height)
{
	int n,i,j;
	float sbar,fbar,ds,df;
	
	sbar = average_template_gray_intensity(template, template_width, template_height);
	fbar = average_template_gray_intensity(cuted_bitmap, template_width, template_height);
	ds = standard_deriv_template(template, template_width, template_height);
	df = standard_deriv_template(cuted_bitmap, template_width, template_height);
	n = template_height * template_width;

	float corr = 0;
	for(i=0;i<template_height * template_width;i++)
	{
		float fraction = (float)(1 / (float)(ds * df));
		corr = (float) ((float)cuted_bitmap[3 * i] - fbar) * ((float)template[3 * i] - sbar);
		corr = (float) fraction * corr;

	}
	corr = (float)((float)1 / n) * corr;
	return corr;
}
void template_matching(unsigned char* bitmap, unsigned char* template, int bitmap_width, int bitmap_height, int template_width, int template_height)
{
	int i, j;
	TM_grayscale(bitmap, bitmap_width, bitmap_height);
	TM_grayscale(template, template_width, template_height);

	for(i=0;i<bitmap_height - template_height;i++)
		for(j=0;j<bitmap_width - template_width;j++)
		{
			unsigned char* cuted_bitmap = cut_template(bitmap, bitmap_width, template_width, template_height, i, j);
			float corr = TM_correlation(cuted_bitmap, template, template_width, template_height);
			if (corr > 0.7) draw_red(bitmap, bitmap_width, template_width, template_height, i, j);
			//printf("%f ", corr);
		}
	return;
}
unsigned char* draw_red(unsigned char* bitmap, int bitmap_width, int template_width, int template_height, int top_i, int top_j)
{
	int i, j, k = 0;

	for (i = top_i; i < template_width + top_i; i++)
	{
		for (j = top_j; j < template_height + top_j; j++)
		{
			int offset = d2(i, j, bitmap_width);
			if (i == template_width + top_i - 1 || i == top_i)bitmap[3 * offset ] = 255;
			if (j == template_height + top_j - 1 || j == top_j)bitmap[3 * offset] = 255;
			
			//printf("(%u, %u, %u)", cuted_template[k - 3], cuted_template[k - 2], cuted_template[k - 1]);
		}
		//printf("\n");
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