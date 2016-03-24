#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

#define imax(x, y) ((x>y) ? x : y)
#define imin(x, y) ((x<y) ? x : y)
#define clipping(x, st, end) (imin(end, imax(st, x)))
#define SQ(x) ((x)*(x))
using namespace cv;

struct colorimg
{
	unsigned char r, g, b;
};

colorimg **IntAlloc2(int width, int height);
colorimg** ReadImage_color(char *name, int *width, int *height);
void WriteImage_color(char* name, colorimg** image, int width, int height);
void Free(colorimg** image, int width, int height);
void lineXY(int cr, double lr, int y, int x, int line_height, int line_width, int o_x, int o_y, int *la_x, int *la_y, int *lb_x, int *lb_y, int *lc_x, int *lc_y, int *ld_x, int *ld_y, float *sub_lx, float *sub_ly);
void bilinearInterpolation2(colorimg** CImg2, colorimg** img, int y, int x, int la_x, int la_y, int lb_x, int lb_y, int lc_x, int lc_y, int ld_x, int ld_y, float sub_lx, float sub_ly);
