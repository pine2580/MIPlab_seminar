#include "header.h"

void main()
{
	int file_count = 0;
	file_count = get_files_count();
	printf("%d\n", file_count);
	
	//vector<wstring> vFileNames = get_files_name(L"C:\\Users\\��۶�\\Desktop\\�۶�������\\�����̳�\\201603\\MunjaDB_IMG20160323\\*.bmp");
	vector<wstring> vFileNames = get_files_name(L"C:\\Users\\��۶�\\Desktop\\�۶�������\\�����̳�\\201603\\test\\*.bmp");

	
	//char *str;
	//sprintf(str, "%ls", vFileNames[0].c_str());
	wcout << vFileNames.size() << endl;
	for (int i = 0; i < vFileNames.size(); i++)
	{
		wcout << vFileNames[i] << endl;
	}
	int width, height;
	//for (int i = 0; i < vFileNames.size(); i++)
	//{
		Mat A = imread("vFileNames[0]",IMREAD_GRAYSCALE);
		imwrite("aaa.bmp", A);
	//}
	
}