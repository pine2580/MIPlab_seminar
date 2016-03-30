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
	feature.ratex = feature.sum1 / feature.sum3;
	feature.ratey = feature.sum2 / feature.sum4;
	//feature.avg4 = feature.sum4 / ((x / 2)*(y / 2));
	//int temp= name.find('[');
	//character.shape = name.Mid(temp, 3);
}
int OptSample(CHARACTER *database_Char, CHARACTER& input_Char,int min_err, int file_count)
{
	double err=0,err2=0;
	double min_err2 = min_err;
	int num=0;
	for (int i = 0; i < file_count; i++)
	{
		err += abs((database_Char[i].avg1 + database_Char[i].avg3) - (input_Char.avg1 + input_Char.avg3));
		err += abs((database_Char[i].avg2 + database_Char[i].avg4) - (input_Char.avg2 + input_Char.avg4));
		if (err < min_err)
		{
			min_err = err;
			err2 += abs((database_Char[i].avg1 - input_Char.avg1));
			err2 += abs((database_Char[i].avg2 - input_Char.avg2));
			err2 += abs((database_Char[i].avg3 - input_Char.avg3));
			err2 += abs((database_Char[i].avg4 - input_Char.avg4));
			if (err2 < min_err2)
			{
				min_err2 = err2;
				num = i;
			}
				
		}
	}
	return num;
}