#include "header.h"

void main()
{
	//int file_count = 0;
	//file_count = get_files_count();
	//printf("%d\n", file_count);

	//vector<wstring> vFileNames = get_files_name(L"C:\\Users\\��۶�\\Desktop\\�۶�������\\�����̳�\\201603\\MunjaDB_IMG20160323\\*.bmp");
	//vector<wstring> vFileNames = get_files_name(L"C:\\Users\\��۶�\\Desktop\\�۶�������\\�����̳�\\201603\\test\\*.bmp");
	vector<wstring> vFileNames = get_files_name(L"C:\\Users\\��۶�\\Documents\\GitHub\\MIPlab_seminar\\character recognition\\character recognition\\*.bmp");

	//char *str;
	//sprintf(str, "%ls", vFileNames[0].c_str());
	//wcout << vFileNames.size() << endl;
	//for (int i = 0; i < vFileNames.size(); i++)
	//{
	//	wcout << vFileNames[i] << endl;
	//}
	//int width, height;
	
	CHARACTER *Database_Char=(CHARACTER *)calloc(vFileNames.size(), sizeof(CHARACTER));
	CHARACTER charname[50];
	int a,b;
	string nameout;
	string test;
	vector<vector< string> > featureArr(600, vector<string>(600));
	int file_count = vFileNames.size();
	for (int i = 0; i < vFileNames.size(); i++)
	{
		test = CW2A(vFileNames[i].c_str());//wstring->string
		Mat A = imread(test, IMREAD_GRAYSCALE);
		// ���ϸ��� ���ĺ� ����
		a = test.find('[');
		b = test.find(']');
		nameout = test.substr(a + 1, b-a-1);
		Database_Char[i].shape = nameout;
 		Char_Feature(A,A.rows,A.cols, Database_Char[i]);//����Ư¡	
		//int y = (int)(Database_Char[i].ratey * 100);
		//int x = (int)(Database_Char[i].ratex * 100);
		//featureArr[y][x] = Database_Char[i].shape;	
	}
	Filename(file_count, Database_Char, charname); //�ߺ��Ǵ� ���� �ϳ���
	Char_Feature_avg(charname, file_count, Database_Char);// Ư¡��հ�

	for (int i = 0; i < 50; i++)
	{
		cout << charname[i].shape<<" "<< charname[i].ratex << "  " << charname[i].ratey << endl;
	}





	//CHARACTER input_Char;
	//Mat B = imread("C:\\Users\\��۶�\\Documents\\GitHub\\MIPlab_seminar\\character recognition\\lineImg.bmp", IMREAD_GRAYSCALE); //�Է� �̹���
	//Binary(B);
	////imshow("input", B);
	////waitKey(0);
	//
	////�󺧸�
	//Mat labelImage(B.rows, B.cols, CV_16UC1);
	//int label_count=connectedComponents(B, labelImage, 8); // 0���� ���Ե� ������
	////imwrite("label.bmp", labelImage);
	//


	//int y_max[255] = { 0 }, x_max[255] = { 0 };
	//int y_min[255], x_min[255];
	//for (int i = 0; i < 255; i++)
	//{
	//	y_min[i] = B.rows;
	//	x_min[i] = B.cols;
	//}
	//
	//Mat C(B.rows, B.cols, CV_8UC1);
	//for (int i = 0; i < B.rows; i++)
	//	for (int j = 0; j < B.cols; j++)
	//	{
	//		C.at<unsigned char>(i, j) = B.at<unsigned char>(i, j);
	//	}
	//
	//Find_MaxMin(labelImage, y_max, x_max, y_min, x_min);
	//MakingBox(labelImage, C,B, y_max, x_max, y_min, x_min, label_count);



	//imwrite("abc.bmp", C);
	//imshow("output", B);
	//waitKey(0);
	/*
	Char_Feature(B, B.rows, B.cols, input_Char);
	int y = (int)(input_Char.ratey * 100);
	int x = (int)(input_Char.ratex * 100);
	double err1, err2;
	double min_err1 = 100.0, min_err2 = 100.0;
	int c, d;
	for (int i = y - 10; i <= y + 10; i++)
		for (int j = x - 10; j <= x + 10; j++)
		{
			if (featureArr[i][j] != NULL)
			{
				err1 = abs(y - i);
				if (err1 < min_err1)
				{
					min_err1 = err1;
					err2 = abs(x - j);
					if (err2 < min_err2)
					{
						min_err2 = err2;
						c= i;
						d = j;
					}
				}

			}
			else
				cout << "����" << endl;
		}
	cout << featureArr[c][d] << endl;
	*/
	
	//����ü ���� Ȯ��
	//opt_num=OptSample(Database_Char, input_Char,min_err,file_count);
		
	
	
	
	
	
}