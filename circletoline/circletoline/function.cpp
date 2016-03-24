#include "헤더.h"

colorimg **IntAlloc2(int width, int height)
{
	colorimg** tmp;

	tmp = (colorimg**)calloc(height, sizeof(colorimg*));
	for (int i = 0; i < height; i++)
		tmp[i] = (colorimg*)calloc(width, sizeof(colorimg));
	return(tmp);
}
colorimg** ReadImage_color(char *name, int *width, int *height)
{
	Mat img = imread(name, CV_LOAD_IMAGE_COLOR);
	colorimg ** image = (colorimg**)IntAlloc2(img.cols, img.rows);

	*width = img.cols;
	*height = img.rows;
	for (int i = 0; i<img.rows; i++)
		for (int j = 0; j < img.cols; j++)
		{
			image[i][j].b = img.at<Vec3b>(i, j)[0]; //B
			image[i][j].g = img.at<Vec3b>(i, j)[1]; //G
			image[i][j].r = img.at<Vec3b>(i, j)[2]; //R
		}
	return(image);
}
void WriteImage_color(char* name, colorimg** image, int width, int height)
{
	Mat img(height, width, CV_8UC3);
	for (int i = 0; i<height; i++)
		for (int j = 0; j<width; j++)
		{
			img.at<Vec3b>(i, j)[0] = (uchar)image[i][j].b;
			img.at<Vec3b>(i, j)[1] = (uchar)image[i][j].g;
			img.at<Vec3b>(i, j)[2] = (uchar)image[i][j].r;
		}
	imwrite(name, img);
}
void Free(colorimg** image, int width, int height)
{
	for (int i = 0; i < height; i++)
		free(image[i]);
	free(image);
}
void circleXY(int i, float r, int o_x, int o_y, int x, int y, int *a_x, int *a_y, int*b_x, int*b_y, int*c_x, int*c_y, int*d_x, int*d_y, float *sub_x, float *sub_y)
{
	double angle;
	float* rx = (float*)calloc(y, sizeof(float)); 	// 이동하는 원의 좌표
	float* ry = (float*)calloc(y, sizeof(float));

	angle = (360.0 / x)*i;
	float rad;
	rad = angle*3.14 / 180;

	for (int j = 0; j < y; j++) //y는 lineimg높이
	{
		rx[j] = o_x + ((r + j)*cos(rad));//원의 좌표
		ry[j] = o_y + ((r + j)*sin(rad));
		a_x[j] = int(rx[j]);
		a_y[j] = int(ry[j]);
		b_x[j] = int(rx[j]) + 1;
		b_y[j] = int(ry[j]);
		c_x[j] = int(rx[j]);
		c_y[j] = int(ry[j]) + 1;
		d_x[j] = int(rx[j]) + 1;
		d_y[j] = int(ry[j]) + 1;
		sub_x[j] = rx[j] - int(rx[j]);
		sub_y[j] = ry[j] - int(ry[j]);
	}
}
void bilinearInterpolation(colorimg** CImg, colorimg** img, int x, int y, int *a_x, int *a_y, int*b_x, int*b_y, int*c_x, int*c_y, int*d_x, int*d_y, float *sub_x, float *sub_y)
{
	for (int j = 0; j <y; j++)
	{
		img[j][x].b = (1 - sub_x[j])*(1 - sub_y[j])*((uchar)CImg[a_x[j]][a_y[j]].b) + sub_x[j] * (1 - sub_y[j])*((uchar)CImg[b_x[j]][b_y[j]].b)
			+ (1 - sub_x[j])*sub_y[j] * ((uchar)CImg[c_x[j]][c_y[j]].b) + sub_x[j] * sub_y[j] * ((uchar)CImg[d_x[j]][d_y[j]].b);
		img[j][x].g = (1 - sub_x[j])*(1 - sub_y[j])*((uchar)CImg[a_x[j]][a_y[j]].g) + sub_x[j] * (1 - sub_y[j])*((uchar)CImg[b_x[j]][b_y[j]].g)
			+ (1 - sub_x[j])*sub_y[j] * ((uchar)CImg[c_x[j]][c_y[j]].g) + sub_x[j] * sub_y[j] * ((uchar)CImg[d_x[j]][d_y[j]].g);
		img[j][x].r = (1 - sub_x[j])*(1 - sub_y[j])*((uchar)CImg[a_x[j]][a_y[j]].r) + sub_x[j] * (1 - sub_y[j])*((uchar)CImg[b_x[j]][b_y[j]].r)
			+ (1 - sub_x[j])*sub_y[j] * ((uchar)CImg[c_x[j]][c_y[j]].r) + sub_x[j] * sub_y[j] * ((uchar)CImg[d_x[j]][d_y[j]].r);
	}
}
