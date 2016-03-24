#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

using namespace cv;
struct colorimg
{
	unsigned char r, g, b;
};

void bilinearInterpolation(colorimg** CImg, colorimg** img, int x, int y, int *a_x, int *a_y, int*b_x, int*b_y, int*c_x, int*c_y, int*d_x, int*d_y, float *sub_x, float *sub_y);
void circleXY(int i, float r, int o_x, int o_y, int x, int y, int *a_x, int *a_y, int*b_x, int*b_y, int*c_x, int*c_y, int*d_x, int*d_y, float *sub_x, float *sub_y);
void Free(colorimg** image, int width, int height);
void WriteImage_color(char* name, colorimg** image, int width, int height);
colorimg** ReadImage_color(char *name, int *width, int *height);
colorimg **IntAlloc2(int width, int height);



