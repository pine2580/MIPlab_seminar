#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>


using namespace cv;
using namespace std;

struct colorimg
{
	unsigned char r, g, b;
};
struct xy
{
	int a_x;
	int a_y;
	int b_x;
	int b_y;
	int c_x;
	int c_y;
	int d_x;
	int d_y;
	double sub_x;
	double sub_y;
};
vector<vector<colorimg> > ReadImage_color(char *name, int *width, int *height)
{
	Mat img = imread(name, CV_LOAD_IMAGE_COLOR);
	vector<vector<colorimg> > image(img.rows, vector<colorimg>(img.cols));

	*width = img.cols;
	*height = img.rows;

	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
		{
			image[i][j].b = img.at<Vec3b>(i, j)[0]; //B
			image[i][j].g = img.at<Vec3b>(i, j)[1]; //G
			image[i][j].r = img.at<Vec3b>(i, j)[2]; //R
		}
	return (image);
}
void WriteImage_color(char* name, vector<vector<colorimg> > image, int width, int height)
{
	Mat img(height, width, CV_8UC3);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			img.at<Vec3b>(i, j)[0] = (uchar)image[i][j].b;
			img.at<Vec3b>(i, j)[1] = (uchar)image[i][j].g;
			img.at<Vec3b>(i, j)[2] = (uchar)image[i][j].r;
		}
	imwrite(name, img);
}
void FindCircleXY(double r1_r,int i, int line_width, int line_height, xy* bilinear, int o_x,int o_y)
{
	double angle;
	double* rx = (double*)calloc(line_height, sizeof(double)); 	// 이동하는 원의 좌표
	double* ry = (double*)calloc(line_height, sizeof(double));
	
	angle = (360.0 / line_width)*i;
	double rad;
	rad = angle*3.1415926535897 / 180;

	for (int j = 0; j < line_height; j++)
	{
		rx[j] = o_x + ((r1_r + j)*cos(rad));
		ry[j] = o_y + ((r1_r + j)*sin(rad));
		//rx.push_back(o_x + ((r1_r + j)*cos(rad)));
		//ry.push_back(o_y + ((r1_r + j)*sin(rad)));
		////xy tmp;
		//tmp.x = int(rx[j]);
		//tmp.y = int(ry[j]);
		//a.push_back(tmp);
		bilinear[j].a_x = int(rx[j]);
		bilinear[j].a_y = int(ry[j]);
		bilinear[j].b_x = int(rx[j])+ 1;
		bilinear[j].b_y = int(ry[j]);
		bilinear[j].c_x = int(rx[j]);
		bilinear[j].c_y = int(ry[j]) + 1;
		bilinear[j].d_x = int(rx[j]) + 1;
		bilinear[j].d_y = int(ry[j]) + 1;
		bilinear[j].sub_x = rx[j] - int(rx[j]);
		bilinear[j].sub_y = ry[j] - int(ry[j]);
	}
	printf("계산끝");
}
void bilinearInterpolation(vector<vector<colorimg> >CircleImg, vector<vector<colorimg> >LineImg, int x, int line_height, xy *bilinear)
{
	for (int j = 0; j <line_height; j++)
	{
		LineImg[j][x].b = (1 - bilinear[j].sub_x)*(1 - bilinear[j].sub_y)*((uchar)CircleImg[bilinear[j].a_x][bilinear[j].a_y].b)+ 
			bilinear[j].sub_x * (1 - bilinear[j].sub_y)*((uchar)CircleImg[bilinear[j].b_x][bilinear[j].b_y].b)+
			(1 - bilinear[j].sub_x)*bilinear[j].sub_y* ((uchar)CircleImg[bilinear[j].c_x][bilinear[j].c_y].b) +
			bilinear[j].sub_x * bilinear[j].sub_y * ((uchar)CircleImg[bilinear[j].d_x][bilinear[j].d_y].b);

		LineImg[j][x].g = (1 - bilinear[j].sub_x)*(1 - bilinear[j].sub_y)*((uchar)CircleImg[bilinear[j].a_x][bilinear[j].a_y].g) +
			bilinear[j].sub_x * (1 - bilinear[j].sub_y)*((uchar)CircleImg[bilinear[j].b_x][bilinear[j].b_y].g) +
			(1 - bilinear[j].sub_x)*bilinear[j].sub_y* ((uchar)CircleImg[bilinear[j].c_x][bilinear[j].c_y].g) +
			bilinear[j].sub_x * bilinear[j].sub_y * ((uchar)CircleImg[bilinear[j].d_x][bilinear[j].d_y].g);

		LineImg[j][x].r = (1 - bilinear[j].sub_x)*(1 - bilinear[j].sub_y)*((uchar)CircleImg[bilinear[j].a_x][bilinear[j].a_y].r) +
			bilinear[j].sub_x * (1 - bilinear[j].sub_y)*((uchar)CircleImg[bilinear[j].b_x][bilinear[j].b_y].r) +
			(1 - bilinear[j].sub_x)*bilinear[j].sub_y* ((uchar)CircleImg[bilinear[j].c_x][bilinear[j].c_y].r) +
			bilinear[j].sub_x * bilinear[j].sub_y * ((uchar)CircleImg[bilinear[j].d_x][bilinear[j].d_y].r);
	}
	printf("선형보간법");
}
void main()
{ 
	int cir_width, cir_height;
	int line_width, line_height; //결과 이미지 가로 세로
	vector<vector<colorimg> > CircleImg = ReadImage_color("C:\\Users\\김송란\\Documents\\네이트온 받은 파일\\숙제2-테스트영상\\크기변환circle.bmp", &cir_width, &cir_height);
	//WriteImage_color("C:\\Users\\김송란\\Documents\\네이트온 받은 파일\\숙제2-테스트영상\\vector_out2.bmp", CircleImg, cir_width, cir_height);

	//int o_x = 6659, o_y = 6659; //원의 중심
	//int r1_x = 11749, r1_y = 6659, r2_x = 13230, r2_y = 6659; //r1은 작은원 r2는 큰원

	int o_x = 1332, o_y = 1334; //원의 중심
	int r1_x = 2350, r1_y = 1334, r2_x = 2610, r2_y = 1334; //원 반지름 1, 2
	double r1_r = r1_x - o_x;//작은원까지의 반지름
	line_width = 5000;
	line_height = r2_x - r1_x;

	xy* bilinear = (xy*)calloc(line_height,sizeof(xy));

	vector<vector<colorimg> > LineImg(line_height, vector<colorimg>(line_width));

	for (int i = 0; i < line_width; i++)
	{
		FindCircleXY(r1_r,i, line_width, line_height, bilinear, o_x, o_y);
		bilinearInterpolation(CircleImg, LineImg, i,line_height, bilinear);
	}
	WriteImage_color("C:\\Users\\김송란\\Documents\\네이트온 받은 파일\\숙제2-테스트영상\\vector_out3.bmp", LineImg, line_width, line_height);


}