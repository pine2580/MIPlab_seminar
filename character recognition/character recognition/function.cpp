#include "header.h"
int** IntAlloc2(int width, int height)
{
	int** tmp;
	tmp = (int**)calloc(height, sizeof(int*));
	for(int i=0;i<height;i++)
		tmp[i] = (int*)calloc(width, sizeof(int));
	return(tmp);
}

void IntFree2(int** image, int width, int height)
{
	for(int i=0;i<height;i++)
		free(image[i]);

	free(image);
}

int** ReadImage(char* name, int* width, int* height)
{
	Mat img = imread(name, IMREAD_GRAYSCALE);
	int** image = (int**)IntAlloc2(img.cols, img.rows);

	*width = img.cols;
	*height = img.rows;

	for(int i=0;i<img.rows;i++)
		for(int j=0;j<img.cols;j++)
			image[i][j] = img.at<unsigned char>(i,j);

	return(image);
}

void WriteImage(char* name, int** image, int width, int height)
{
	Mat img(height, width, CV_8UC1);
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			img.at<unsigned char>(i,j) = (unsigned char)image[i][j];
	
	imwrite(name, img);
}
int get_files_count()
{
	bool x = true;
	int i = 0;
	wchar_t* file = L"C:\\Users\\김송란\\Desktop\\송란이폴더\\랩세미나\\201603\\MunjaDB_IMG20160323\\*.bmp";
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile(file, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		i++;
		while ((x = FindNextFile(hFind, &FindFileData)) == TRUE)
				i++;
	}
	return i;
}
vector<wstring> get_files_name(wstring directory)
{
	vector<wstring> files;
	WIN32_FIND_DATA fd;
	HANDLE hFind= FindFirstFile(directory.c_str(), &fd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				files.push_back(fd.cFileName);

		}
		while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}
	return files;
}
void Char_Feature(Mat A, int y, int x,CHARACTER& feature)
{
	//char search = '[';
	feature.sum1=0, feature.sum2 = 0,feature.sum3=0,feature.sum4=0;
	feature.ratex = 0, feature.ratey = 0;
	feature.avg1 = 0, feature.avg2 = 0, feature.avg3 = 0, feature.avg4 = 0;
	for (int i = 0; i < y/2; i++)
		for (int j = 0; j < x/2; j++)
		{
			if (A.at<uchar>(i, j) == 255)
				feature.sum1 += 1;
		}
	//feature.avg1 = feature.sum1 / ((x/2)*(y/2));
	for (int i = 0; i < y / 2; i++)
		for (int j = x/2; j < x; j++)
		{
			if (A.at<uchar>(i, j) == 255)
				feature.sum2 += 1;
		}
	//feature.avg2 = feature.sum2 / ((x / 2)*(y / 2));
	for (int i = y/2; i < y; i++)
		for (int j = 0; j < x / 2; j++)
		{
			if (A.at<uchar>(i, j) == 255)
				feature.sum3 += 1;
		}
	//feature.avg3 = feature.sum3 / ((x / 2)*(y / 2));
	for (int i = y/2; i < y; i++)
		for (int j = x/2; j < x; j++)
		{
			if (A.at<uchar>(i, j) == 255)
				feature.sum4 += 1;
		}
	feature.ratex = (feature.sum1 +feature.sum3)/ (feature.sum2+feature.sum4);
	feature.ratey = (feature.sum1+feature.sum2) / (feature.sum3+feature.sum4);
	feature.avg1 = ((feature.sum1 + feature.sum3) / (x*y))*100;
	feature.avg2 = ((feature.sum2 + feature.sum3) / (x*y)) * 100;
	feature.avg3 = ((feature.sum1 + feature.sum2) / (x*y)) * 100;
	feature.avg4 = ((feature.sum3 + feature.sum4) / (x*y)) * 100;

	//feature.avg4 = feature.sum4 / ((x / 2)*(y / 2));
	//int temp= name.find('[');
	//character.shape = name.Mid(temp, 3);
}
void Filename(int file_count, CHARACTER* feature, CHARACTER *charname)
{
	int count ;
	int n = 0;
	int m;
	for (int i = 0; i < file_count; i++)
	{
		count = 0;
		for (int j = 0; j <50; j++)
		{
			if (charname[j].shape.compare(feature[i].shape) == 0)
			{
				count++;
			}
		}
		if (count == 0)
		{
			charname[n].shape = feature[i].shape;
			n++;
		}
	}
}
void Char_Feature_avg(CHARACTER* charname,int file_count, CHARACTER *feature)
{
	int n;
	for (int i = 0; i < 50; i++)
	{
		n = 0;
		charname[i].ratex = 0;
		charname[i].ratey = 0;
		charname[i].avg1 = 0, charname[i].avg2 = 0, charname[i].avg3 = 0, charname[i].avg4 = 0;
		for (int j = 0; j < file_count; j++)
		{
			if (charname[i].shape.compare(feature[j].shape) == 0)
			{
				charname[i].ratex += feature[j].ratex;
				charname[i].ratey += feature[j].ratey;
				charname[i].avg1 += feature[j].avg1;
				charname[i].avg2 += feature[j].avg2;
				charname[i].avg3 += feature[j].avg3;
				charname[i].avg4 += feature[j].avg4;
				n++;
			}
		}
		charname[i].ratex = charname[i].ratex / n;
		charname[i].ratey = charname[i].ratey / n;
		charname[i].avg1 = charname[i].avg1/n;
		charname[i].avg2 = charname[i].avg2/n;
		charname[i].avg3 = charname[i].avg3/n;
		charname[i].avg4 = charname[i].avg4/n;
	}
}
void OptSample(CHARACTER *charname, CHARACTER &input_Char, int*Optnum)
{
	double err1 = 0, err2 = 0, err = 0;
	double min_err1 = 10, min_err2 = 10, min_err = 20.0;
	double avg_err, avg_minerr = 10;
	int num=0;
	int num1 = 0, num2 = 0, num3 = 0;
	double sub_err1, sub_err2, sub_err3, sub_err4;
	double part4err = 0;
	double part4_minerr = 100*100;
	//for (int i = 0; i < 48; i++)
	//{
	//	err = (abs(charname[i].ratex - ratex)) + (abs(charname[i].ratey - ratey));
	//	if (err <0.15)
	//	{
	//		avg_err = abs(charname[i].avg1 - avg1) + abs(charname[i].avg2 - avg2) + abs(charname[i].avg3 - avg3) + abs(charname[i].avg4 - avg4);
	//		if (avg_err < avg_minerr)
	//		{
	//			num = i;
	//			avg_minerr = avg_err;
	//		}
	//			
	//	}
	//}
	//*Optnum = num;
	for (int i = 0; i < 50; i++)
	{
		sub_err1 = abs(charname[i].avg1 - input_Char.avg1);
		sub_err2 = abs(charname[i].avg2 - input_Char.avg2);
		sub_err3 = abs(charname[i].avg3 - input_Char.avg3);
		sub_err4 = abs(charname[i].avg4 - input_Char.avg4);
		part4err = sub_err1 + sub_err2 + sub_err3 + sub_err4;
		if(part4err<part4_minerr)
		{
			part4_minerr = part4err;
			num = i;
		}
	}
	*Optnum = num;
}
void QuickSort(double *ar, int num)

{
	int left, right;
	char key;

	if (num <= 1) return;
	// 기준값 결정 : 배열상의 제일 끝 요소
	key = ar[num - 1];
	for (left = 0, right = num - 2;; left++, right--)
	{
		while (ar[left] < key)
		{
			left++;
		}
		while (ar[right] > key)
		{
			right--;
		}

		if (left >= right) break;            // 좌우가 만나면 끝
		SWAP(ar[left], ar[right]);

	}
	SWAP(ar[left], ar[num - 1]);                   // 기준값과 i위치의 값 교환
	QuickSort(ar, left);                           // 왼쪽 구간 정렬
	QuickSort(ar + left + 1, num - left - 1);        // 오른쪽 구간 정렬
}

void Binary(Mat B)
{
	for (int i = 0; i < B.rows; i++)
	{
		for (int j = 0; j < B.cols; j++)
			if (B.at<unsigned char>(i, j) > 130) B.at<unsigned char>(i, j) = 0;
			else B.at<unsigned char>(i, j) = 255;
	}
	dilate(B, B, Mat(), Point(-1, -1), 1); //팽창
	erode(B, B, Mat(), Point(-1, -1), 1);  //침식
}
void Find_MaxMin(Mat B,int* y_max,int* x_max,int* y_min,int* x_min)
{
	int y_temp = 0, x_temp = 0;
	//라벨의 좌표 최대 최소 찾기
	for (int i = 0; i <B.rows; i++)
	{
		for (int j = 0; j <B.cols; j++)
		{
			if (B.at<int>(i, j) >= 1)
			{
				y_temp = i;
				x_temp = j;
				y_max[B.at<int>(i, j)] = MAX(y_max[B.at<int>(i, j)], y_temp);
				y_min[B.at<int>(i, j)] = MIN(y_min[B.at<int>(i, j)], y_temp);
				x_max[B.at<int>(i, j)] = MAX(x_max[B.at<int>(i, j)], x_temp);
				x_min[B.at<int>(i, j)] = MIN(x_min[B.at<int>(i, j)], x_temp);
			}
		}
	}
}
void MakingBox(Mat in, Mat out, Mat B, int* y_max, int* x_max, int* y_min, int* x_min,int label_count)
{

	int x=0, y=0;
	int *temp = (int*)calloc(label_count, sizeof(int));
	for (int i = 1; i < label_count; i++)
	{
		for (int j = y_min[i]; j < y_max[i]; j++)
		{
			for (int k = x_min[i]; k < x_max[i]; k++)
			{
				if (temp[i] != 1)
				{
					if ((in.at<int>(j, k) != 0) && (in.at<int>(j, k) != i))
					{
						if ((y_max[in.at<int>(j, k)] < y_max[i]) && (x_max[in.at<int>(j, k)] < x_max[i]) && (y_min[in.at<int>(j, k)] > y_min[i]) && (x_min[in.at<int>(j, k)] > x_min[i]))
						{
							//C.at<uchar>(j, k) = B.at<uchar>(j, k);
							temp[in.at<int>(j, k)] = 1;
						}
					}
				}
			}
		}
			
	}
	for (int i = 1; i < label_count; i++)
	{
		if (temp[i] != 1)
		{
			y = y_min[i];
			for (x = x_min[i]; x <= x_max[i]; x++)
				out.at<unsigned char>(y, x) = 255;
			y = y_max[i];
			for (x = x_min[i]; x <= x_max[i]; x++)
				out.at<unsigned char >(y, x) = 255;
			x = x_min[i];
			for (y = y_min[i]; y <= y_max[i]; y++)
				out.at<unsigned char>(y, x) = 255;
			x = x_max[i];
			for (y = y_min[i]; y <= y_max[i]; y++)
				out.at<unsigned char>(y, x) = 255;
		}
	}	
}
