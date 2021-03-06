#pragma once
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

#include <direct.h>

#include <io.h>
#include <conio.h>

#include <atlstr.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define SWAP(a,b) int temp=a; a=b; b=temp;
using namespace std;
using namespace cv;

typedef struct
{
	double sum1, sum2, sum3, sum4;
	double avg1, avg2, avg3, avg4;
	double ratex, ratey;
	string shape;
	BOOL flag;
}CHARACTER;

int** IntAlloc2(int width, int height);
void IntFree2(int** image, int width, int height);
int** ReadImage(char* name, int* width, int* height);
void WriteImage(char* name, int** image, int width, int height);
int get_files_count();
vector<wstring> get_files_name(wstring);
void Char_Feature(Mat,int,int,CHARACTER&);
void OptSample(CHARACTER*, CHARACTER& ,int*);
void Binary(Mat);
void Find_MaxMin(Mat B, int* y_max, int* x_max, int* y_min, int* x_min);
void MakingBox(Mat ,Mat,Mat ,int* y_max, int* x_max, int* y_min, int* x_min, int label_count);
void Char_Feature_avg(CHARACTER*, int count, CHARACTER* );
void Filename(int file_count, CHARACTER* feature, CHARACTER *charname);