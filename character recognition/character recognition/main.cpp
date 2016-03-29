#include "header.h"

void main()
{
	int file_count = 0;
	file_count = get_files_count();
	printf("%d\n", file_count);

	//vector<wstring> vFileNames = get_files_name(L"C:\\Users\\김송란\\Desktop\\송란이폴더\\랩세미나\\201603\\MunjaDB_IMG20160323\\*.bmp");
	vector<wstring> vFileNames = get_files_name(L"C:\\Users\\김송란\\Desktop\\송란이폴더\\랩세미나\\201603\\test\\*.bmp");


	//char *str;
	//sprintf(str, "%ls", vFileNames[0].c_str());
	wcout << vFileNames.size() << endl;
	for (int i = 0; i < vFileNames.size(); i++)
	{
		wcout << vFileNames[i] << endl;
	}
	int width, height;
	
		string test=CW2A(vFileNames[0].c_str());
		Mat A = imread(test, IMREAD_GRAYSCALE);
		imwrite("aaa.bmp", A);

		

	
}