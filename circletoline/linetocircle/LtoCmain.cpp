#include "linetocircle_header.h"
void main()
{
	int cir_width, line_width;
	int cir_height, line_height;
	//int o_x = 1332, o_y = 1334; //원의 중심
	//int r1_x = 2350, r1_y = 1334, r2_x = 2610, r2_y = 1334; //원 반지름 1, 2

	int o_x = 6659, o_y = 6659; //원의 중심
	int r1_x = 11749, r1_y = 6664, r2_x = 13230, r2_y = 6664;


	colorimg** CImg2 = ReadImage_color("C:\\Users\\김송란\\Documents\\네이트온 받은 파일\\숙제2-테스트영상\\크기수정line.bmp", &line_width, &line_height);
	int cr = r1_x - o_x;
	int circle_width = o_x + line_height + cr + 20;
	int circle_height = o_y + line_height + cr + 20;
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

	for (int i = 0; i < circle_height; i++)
		for (int j = 0; j < circle_width; j++)
		{
			lr = sqrt(pow(j - o_x, 2) + pow(i - o_y, 2));//원의 방정식을 만족하는 x,y를 찾는다.
			if (cr <= lr&&lr<cr + line_height - 2)
			{
				lineXY(cr, lr, i, j, line_height, line_width, o_x, o_y, &la_x, &la_y, &lb_x, &lb_y, &lc_x, &lc_y, &ld_x, &ld_y, &sub_lx, &sub_ly);
				bilinearInterpolation2(CImg2, circleimg, i, j, la_x, la_y, lb_x, lb_y, lc_x, lc_y, ld_x, ld_y, sub_lx, sub_ly);
			}
			else
			{
				circleimg[i][j].b = 255;
				circleimg[i][j].g = 255;
				circleimg[i][j].r = 255;
			}
		}


	WriteImage_color("C:\\Users\\김송란\\Documents\\네이트온 받은 파일\\숙제2-테스트영상\\linetocircle7.bmp", circleimg, circle_width, circle_height);
	Free(circleimg, circle_width, circle_height);
	Free(CImg2, line_width, line_height);
}
