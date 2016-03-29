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