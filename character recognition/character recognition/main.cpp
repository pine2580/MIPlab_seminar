#include "header.h"

void main()
{
	//int file_count = 0;
	//file_count = get_files_count();
	//printf("%d\n", file_count);

	//vector<wstring> vFileNames = get_files_name(L"C:\\Users\\��۶�\\Desktop\\�۶�������\\�����̳�\\201603\\MunjaDB_IMG20160323\\*.bmp");
	//vector<wstring> vFileNames = get_files_name(L"C:\\Users\\��۶�\\Desktop\\�۶�������\\�����̳�\\201603\\test\\*.bmp");
	vector<wstring> vFileNames = get_files_name(L"*.bmp");

	//char *str;
	//sprintf(str, "%ls", vFileNames[0].c_str());
	//wcout << vFileNames.size() << endl;
	//for (int i = 0; i < vFileNames.size(); i++)
	//{
	//	wcout << vFileNames[i] << endl;
	//}
	//int width, height;
	
	CHARACTER *Database_Char=(CHARACTER *)calloc(vFileNames.size(), sizeof(CHARACTER));
	

	string test;
	
	// ���ϸ��� ���ĺ� ����
	string temp;
	temp = CW2A(vFileNames[0].c_str());
	int a=temp.find('[');
	string nameout=	temp.substr(a + 1, 1);
	cout << nameout << endl;
	
	for (int i = 0; i < vFileNames.size(); i++)
	{
		test = CW2A(vFileNames[i].c_str());//wstring->string
		Mat A = imread(test, IMREAD_GRAYSCALE);
		//imshow("out", A);
		//waitKey(0);
 		Char_Feature(A,A.rows,A.cols, Database_Char[i]);
		//imwrite("aaa.bmp", A);
	//	printf("%lf\n", databasechar[i].avg);
	}
	

	CHARACTER input_Char;
	Mat B = imread("C:\\Users\\��۶�\\Documents\\GitHub\\MIPlab_seminar\\test.bmp", IMREAD_GRAYSCALE); //�Է� �̹���
	for (int i = 0; i < B.rows; i++)
		for (int j = 0; j < B.cols; j++)
		{
			Char_Feature(B, B.rows, B.cols, input_Char);
		}
	imshow("input", B);
	
	int file_count = vFileNames.size();
	double min_err = B.cols*B.rows;
	int opt_num;
	
	����ü ���� Ȯ��
	opt_num=OptSample(Database_Char, input_Char,min_err,file_count);
		
	test = CW2A(vFileNames[opt_num].c_str());
	Mat out = imread(test, IMREAD_GRAYSCALE);
	imshow("������", out);
	waitKey(0);
	
}