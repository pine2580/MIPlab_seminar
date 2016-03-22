#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

#define MAX(a,b) (a)>(b) ? (a):(b)
#define MIN(a,b) (a)<(b) ? (a):(b)
using namespace cv;

struct colorimg
{
	unsigned char r, g, b;
};

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
		rx[j] = o_x + ((r+j)*cos(rad));//원의 좌표
		ry[j] = o_y + ((r+j)*sin(rad));
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
	for (int j =0; j <y ; j++)
	{
		img[j][x].b = (1 - sub_x[j])*(1 - sub_y[j])*((uchar)CImg[a_x[j]][a_y[j]].b) + sub_x[j] * (1 - sub_y[j])*((uchar)CImg[b_x[j]][b_y[j]].b)
			+ (1 - sub_x[j])*sub_y[j] * ((uchar)CImg[c_x[j]][c_y[j]].b) + sub_x[j] * sub_y[j] * ((uchar)CImg[d_x[j]][d_y[j]].b);
		img[j][x].g = (1 - sub_x[j])*(1 - sub_y[j])*((uchar)CImg[a_x[j]][a_y[j]].g) + sub_x[j] * (1 - sub_y[j])*((uchar)CImg[b_x[j]][b_y[j]].g)
			+ (1 - sub_x[j])*sub_y[j] * ((uchar)CImg[c_x[j]][c_y[j]].g) + sub_x[j] * sub_y[j] * ((uchar)CImg[d_x[j]][d_y[j]].g);
		img[j][x].r = (1 - sub_x[j])*(1 - sub_y[j])*((uchar)CImg[a_x[j]][a_y[j]].r) + sub_x[j] * (1 - sub_y[j])*((uchar)CImg[b_x[j]][b_y[j]].r)
			+ (1 - sub_x[j])*sub_y[j] * ((uchar)CImg[c_x[j]][c_y[j]].r) + sub_x[j] * sub_y[j] * ((uchar)CImg[d_x[j]][d_y[j]].r);
	}
}
void lineXY(int r2,double lr,int y, int x,int line_height,int line_width,int o_x, int o_y, int *la_x, int *la_y, int *lb_x, int *lb_y, int *lc_x, int *lc_y, int *ld_x, int *ld_y, float *sub_lx, float *sub_ly)
{
	double cos_tmp,sin_tmp;
	double lx; 	//라인 좌표
	double ly;
		ly = lr-r2;
		//lx = acos((x - o_x+1) / lr);
		//lx = pow(cos((x - o_x + 1) / lr), -1);
		cos_tmp = pow(cos(x / lr), -1);
			lx = cos_tmp / (360.0 / line_width);
			*la_x = int(lx);
			*la_y = int(ly);
			*lb_x = int(lx) + 1;
			*lb_y = int(ly);
			*lc_x = int(lx);
			*lc_y = int(ly) + 1;
			*ld_x = int(lx) + 1;
			*ld_y = int(ly) + 1;
			*sub_lx = lx - int(lx);
			*sub_ly = ly - int(ly);
		
		
}
void bilinearInterpolation2(colorimg** CImg2, colorimg** img, int y, int x, int la_x, int la_y, int lb_x, int lb_y, int lc_x, int lc_y, int ld_x, int ld_y, float sub_lx, float sub_ly)
{
		img[y][x].b = (1 - sub_lx)*(1 - sub_ly)*((uchar)CImg2[la_y][la_x].b) + sub_lx * (1 - sub_ly)*((uchar)CImg2[lb_y][lb_x].b)
			+ (1 - sub_lx)*sub_ly * ((uchar)CImg2[lc_y][lc_x].b) + sub_lx * sub_ly * ((uchar)CImg2[ld_y][ld_x].b);
		img[y][x].g = (1 - sub_lx)*(1 - sub_ly)*((uchar)CImg2[la_y][la_x].g) + sub_lx * (1 - sub_ly)*((uchar)CImg2[lb_y][lb_x].g)
			+ (1 - sub_lx)*sub_ly * ((uchar)CImg2[lc_y][lc_x].g) + sub_lx * sub_ly * ((uchar)CImg2[ld_y][ld_x].g);
		img[y][x].r = (1 - sub_lx)*(1 - sub_ly)*((uchar)CImg2[la_y][la_x].r) + sub_lx * (1 - sub_ly)*((uchar)CImg2[lb_y][lb_x].r)
			+ (1 - sub_lx)*sub_ly * ((uchar)CImg2[lc_y][lc_x].r) + sub_lx * sub_ly * ((uchar)CImg2[ld_y][ld_x].r);
	
}
void main()
{

	int cir_width, line_width;
	int cir_height, line_height;
	//int o_x = 1332, o_y = 1334; //원의 중심
	//int r1_x = 2350, r1_y = 1334, r2_x = 2610, r2_y = 1334; //원 반지름 1, 2

	int o_x = 6660, o_y = 6664; //원의 중심
	int r1_x = 11740, r1_y = 6664, r2_x=13052, r2_y=6664;
	
	/*
	colorimg** CImg = ReadImage_color("C:\\Users\\김송란\\Documents\\네이트온 받은 파일\\숙제2-테스트영상\\circle2.bmp", &cir_width, &cir_height);
	line_width = 10000;
	line_height = r2_x-r1_x;
	int* a_x = (int*)calloc(line_height, sizeof(int));
	int* a_y = (int*)calloc(line_height, sizeof(int));
	int* b_x = (int*)calloc(line_height, sizeof(int));
	int* b_y = (int*)calloc(line_height, sizeof(int));
	int* c_x = (int*)calloc(line_height, sizeof(int));
	int* c_y = (int*)calloc(line_height, sizeof(int));
	int* d_x = (int*)calloc(line_height, sizeof(int));
	int* d_y = (int*)calloc(line_height, sizeof(int));
	float* sub_x = (float*)calloc(line_height, sizeof(float));
	float* sub_y = (float*)calloc(line_height, sizeof(float));
	float r; //반지름
	r = r1_x - o_x;
	colorimg** lineimg = (colorimg**)IntAlloc2(line_width, line_height);

	for (int i = 0; i <line_width; i++)//가로로 한줄씩
	{
		circleXY(i, r, o_x, o_y, line_width, line_height, a_x, a_y, b_x, b_y, c_x, c_y, d_x, d_y, sub_x, sub_y);
		bilinearInterpolation(CImg, lineimg, i, line_height, a_x, a_y, b_x, b_y, c_x, c_y, d_x, d_y, sub_x, sub_y);
	}
	WriteImage_color("C:\\Users\\김송란\\Documents\\네이트온 받은 파일\\숙제2-테스트영상\\확인2.bmp", lineimg, line_width, line_height);

	Free(CImg, cir_width, cir_height);
	Free(lineimg, line_width, line_height);
	*/
	


	colorimg** CImg2 = ReadImage_color("C:\\Users\\김송란\\Documents\\네이트온 받은 파일\\숙제2-테스트영상\\확인2.bmp", &line_width, &line_height);
	int r2 = r1_x - o_x;
	int circle_width = o_x + line_height+r2+10;
	int circle_height = o_y + line_height +r2+10;
	double lr;
	colorimg** circleimg = (colorimg**)IntAlloc2(circle_width, circle_height);
	int la_x;
	int la_y;
	int lb_x;
	int lb_y;
	int lc_x;
	int lc_y;
	int ld_x;
	int ld_y;
	float sub_lx;
	float sub_ly;

	for (int i = 11000; i < circle_height; i++)
		for (int j =1600 ; j < circle_width; j++)
		{
			lr = sqrt(pow(j - o_x, 2) + pow(i - o_y, 2));//원의 방정식을 만족하는 x,y를 찾는다.
			if (r2<lr&&lr<r2+line_height-3)
			{
				//printf("%lf", acos(1993 / lr));
				lineXY(r2,lr,i, j, line_height, line_width, o_x, o_y, &la_x, &la_y, &lb_x, &lb_y, &lc_x, &lc_y, &ld_x, &ld_y, &sub_lx, &sub_ly);
				bilinearInterpolation2(CImg2, circleimg, i, j, la_x, la_y, lb_x, lb_y, lc_x, lc_y, ld_x, ld_y, sub_lx, sub_ly);
			}
			else
			{
				circleimg[j][i].b = 255;
				circleimg[j][i].g = 255;
				circleimg[j][i].r = 255;
			}
		}

	WriteImage_color("C:\\Users\\김송란\\Documents\\네이트온 받은 파일\\숙제2-테스트영상\\linetocircle3.bmp", circleimg, circle_width, circle_height);
	Free(circleimg, circle_width, circle_height);
	Free(CImg2, line_width, line_height);
}