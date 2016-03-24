#include "헤더.h"

void main()
{

	int cir_width, line_width;
	int cir_height, line_height;
	//int o_x = 1332, o_y = 1334; //원의 중심
	//int r1_x = 2350, r1_y = 1334, r2_x = 2610, r2_y = 1334; //원 반지름 1, 2
	int o_x = 6659, o_y = 6659; //원의 중심
	int r1_x = 11749, r1_y = 6664, r2_x=13230, r2_y=6664;
	
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

}