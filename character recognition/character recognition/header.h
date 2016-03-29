#pragma once
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>

#include <direct.h>

#include <io.h>
#include <conio.h>

#include <atlstr.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

typedef struct
{
	int part1;
	int part2;
	int part3;
	int part4;
	char shape;
};
int** IntAlloc2(int width, int height);
void IntFree2(int** image, int width, int height);
int** ReadImage(char* name, int* width, int* height);
void WriteImage(char* name, int** image, int width, int height);
int get_files_count();
vector<wstring> get_files_name(wstring);