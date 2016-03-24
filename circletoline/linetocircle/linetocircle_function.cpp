#include "linetocircle_header.h"
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

void lineXY(int cr, double lr, int y, int x, int line_height, int line_width, int o_x, int o_y, int *la_x, int *la_y, int *lb_x, int *lb_y, int *lc_x, int *lc_y, int *ld_x, int *ld_y, float *sub_lx, float *sub_ly)
{
	double cos_tmp, sin_tmp;
	double lx; 	//¶óÀÎ ÁÂÇ¥
	double ly;
	ly = lr - cr;
	cos_tmp = acos(((double)x - o_x) / lr);
	double angle = cos_tmp*180.0 / 3.14;
	if (y>o_x)
		lx = (360.0 - angle) / (360.0 / line_width);
	else
		lx = angle / (360.0 / line_width);
	clipping(lx, 0, line_height - 2);
	clipping(ly, 0, line_height - 2);
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
