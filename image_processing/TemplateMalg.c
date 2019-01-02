#include "TemplateMalg.h"
#include <math.h>
#include "bitmapIO.h"
int qsort_comparator(const void *p, const void *q)
{
	detection x, y;
	x = *(detection*)p;
	y = *(detection*)q;
	if (x.corr < y.corr) return -1;
	if (x.corr > y.corr) return 1;
	return 0;
}
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
	
	for (i = top_i; i < template_height + top_i; i++)
	{
		for (j = top_j; j < template_width + top_j; j++)
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
		float pow = (float)template[i * 3] - sbar;
		pow = pow * pow;
		deriv += pow;
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
		
		float mult = ((float)cuted_bitmap[3 * i] - fbar) * ((float)template[3 * i] - sbar);
		float derivor = ds * df;
		corr = corr + mult / derivor;
		

	}
	corr = (float) corr / n;
	return corr;
}
void template_matching(unsigned char* bitmap, int bitmap_width, int bitmap_height)
{
	int i, j, k = -1;
	TM_grayscale(bitmap, bitmap_width, bitmap_height);
	
	//color declaration

		color* color_ar;
		color_ar = malloc(10 * sizeof(color));
	

		color_ar[0].R = 255;
		color_ar[0].G = 0;
		color_ar[0].B = 0;

		color_ar[1].R = 255;
		color_ar[1].G = 255;
		color_ar[1].B = 0;

		color_ar[2].R = 0;
		color_ar[2].G = 255;
		color_ar[2].B = 0;

		color_ar[3].R = 0;
		color_ar[3].G = 255;
		color_ar[3].B = 255;

		color_ar[4].R = 255;
		color_ar[4].G = 0;
		color_ar[4].B = 255;

		color_ar[5].R = 0;
		color_ar[5].G = 0;
		color_ar[5].B = 25;

		color_ar[6].R = 192;
		color_ar[6].G = 192;
		color_ar[6].B = 192;

		color_ar[7].R = 255;
		color_ar[7].G = 140;
		color_ar[7].B = 0;

		color_ar[8].R = 128;
		color_ar[8].G = 0;
		color_ar[8].B = 128;

		color_ar[9].R = 128;
		color_ar[9].G = 0;
		color_ar[9].B = 0;
	

	detection *dect_ar;
	dect_ar = malloc(1000 * sizeof(detection));
	
	unsigned char** template_name_ar;
	template_name_ar = malloc(11 * sizeof(unsigned char*));

	for (i = 0; i <= 10; i++)
		template_name_ar[i] = malloc(15 * sizeof(unsigned char));

	template_name_ar[0] = "cifra0.bmp";
	template_name_ar[1] = "cifra1.bmp";
	template_name_ar[2] = "cifra2.bmp";
	template_name_ar[3] = "cifra3.bmp";
	template_name_ar[4] = "cifra4.bmp";
	template_name_ar[5] = "cifra5.bmp";
	template_name_ar[6] = "cifra6.bmp";
	template_name_ar[7] = "cifra7.bmp";
	template_name_ar[8] = "cifra8.bmp";
	template_name_ar[9] = "cifra9.bmp";

	int number_cnt;
	unsigned char* template;
	int template_width, template_height;
	for (number_cnt = 0; number_cnt <= 9; number_cnt++)
	{ //number_cnt = 0;
		template = bitmap_load(template_name_ar[number_cnt]);
		template_width = bitmap_data_width(template_name_ar[number_cnt]);
		template_height = bitmap_data_height(template_name_ar[number_cnt]);

		TM_grayscale(template, template_width, template_height);

		for (i = 0; i <= bitmap_height - template_height; i++)
			for (j = 0; j <= bitmap_width - template_width; j++)
			{
				unsigned char* cuted_bitmap = cut_template(bitmap, bitmap_width, template_width, template_height, i, j);
				float corr = TM_correlation(cuted_bitmap, template, template_width, template_height);
				if (corr > 0.5)
				{
					++k;
					dect_ar[k].corr = corr;
					dect_ar[k].top_i = i;
					dect_ar[k].top_j = j;
					dect_ar[k].number = number_cnt;
					draw_rect(bitmap, bitmap_width, template_width, template_height, i, j, color_ar[number_cnt]);
				}
				//printf("%f ", corr);
				free(cuted_bitmap);

			}

	}
	k++;
	qsort((void*)dect_ar, k, sizeof(detection), qsort_comparator);
	non_max(dect_ar, k, template_width, template_height);

	return;

}
void draw_rect(unsigned char* bitmap, int bitmap_width, int template_width, int template_height, int top_i, int top_j, color color_rgb)
{
	int i, j, k = 0;
	//printf("%d %d", top_i, top_j);
	for (i = top_i; i < template_height + top_i; i++)
	{
		for (j = top_j; j < template_width + top_j; j++)
		{
			int offset = d2(i, j, bitmap_width);
			if (i == template_height + top_i - 1 || i == top_i)
			{
				bitmap[3 * offset + 0] = color_rgb.R;
				bitmap[3 * offset + 1] = color_rgb.G;
				bitmap[3 * offset + 2] = color_rgb.B;

			}

			if (j == template_width + top_j - 1 || j == top_j)
			{
				bitmap[3 * offset + 0] = color_rgb.R;
				bitmap[3 * offset + 1] = color_rgb.G;
				bitmap[3 * offset + 2] = color_rgb.B;
			}
			
		}
		
	}
}
int area_sup(int di_x, int di_y, int dj_x, int dj_y, int width, int height)
{
	float di_area, dj_area;

	di_area = width * height;
	dj_area = width * height;

	int inter_height = (di_x + height) - (dj_x + height);
	int inter_width = (di_y + width) - (dj_y + width);

	if (inter_width < 0) inter_width = inter_width * (-1);
	if (inter_height < 0) inter_height = inter_height * (-1);

	if (inter_width > width && inter_height > height) return 0;
	float inter_area = inter_width * inter_height;
	float sup;
	sup = (inter_area) / (di_area + dj_area - inter_area);

	if (sup > 0.2) return 1;

	return 0;
}
void non_max(detection *dect_ar, int n, int template_width, int template_height)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
		{
			int di_x, di_y, dj_x, dj_y;
			di_x = dect_ar[i].top_i;
			di_y = dect_ar[i].top_j;
			dj_x = dect_ar[j].top_i;
			dj_y = dect_ar[j].top_j;

			if (area_sup(di_x, di_y, dj_x, dj_y, template_width, template_height) && dect_ar[i].corr > -1 && dect_ar[j].corr > -1)
			{
				dect_ar[j].corr = -2;
			}
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