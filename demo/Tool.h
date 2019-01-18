
#include <iostream>
#include <sys/types.h>
#include <time.h> 
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <opencv2/opencv.hpp>

using namespace  std;
using namespace cv;
using namespace ml;

namespace Tool {


	long getTimeLabel();
	void drawRectangle(Mat& img, Rect box);
	vector<string> listFiles(string dir);





	void printTime(){
		time_t tt = time(NULL);//��䷵�ص�ֻ��һ��ʱ���
		tm* t = localtime(&tt);
		printf("%d-%02d-%02d %02d:%02d:%02d\n",
			t->tm_year + 1900,
			t->tm_mon + 1,
			t->tm_mday,
			t->tm_hour,
			t->tm_min,
			t->tm_sec);

		printf("now:%li", getTimeLabel());
	}

	long getTimeLabel(){
		time_t now_time;
		now_time = time(NULL);

		return now_time;
	}


	void drawRectangle(Mat& img, Rect box){

		rectangle(img, box.tl(), box.br(), Scalar(200, 88, 88));

	}
	/*
	�����õķ�ʽ�õ�Ŀ¼�������ļ�
	*/
	void getFiles(string path, vector<string>& files)
	{
		//�ļ����  
		long   hFile = 0;
		//�ļ���Ϣ������һ���洢�ļ���Ϣ�Ľṹ��  
		struct _finddata_t fileinfo;
		string p;//�ַ��������·��
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//�����ҳɹ��������
		{
			do
			{
				//�����Ŀ¼,����֮�����ļ����ڻ����ļ��У�  
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					//�ļ���������"."&&�ļ���������".."
					//.��ʾ��ǰĿ¼
					//..��ʾ��ǰĿ¼�ĸ�Ŀ¼
					//�ж�ʱ�����߶�Ҫ���ԣ���Ȼ�����޵ݹ�������ȥ�ˣ�
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
				//�������,�����б�  
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			//_findclose������������
			_findclose(hFile);
		}
	}

	/*
	*�õ�Ŀ¼�������ļ�
	*
	*/
	vector<string> listFiles(string dirRoot){
		
		vector<string> subfiles;
		//�ļ����  
		long   hFile = 0;
		//�ļ���Ϣ������һ���洢�ļ���Ϣ�Ľṹ��  
		struct _finddata_t fileinfo;
		string p;//�ַ��������·��
		if ((hFile = _findfirst(p.assign(dirRoot).append("/*").c_str(), &fileinfo)) != -1)//�����ҳɹ��������
		{
			do
			{
				//�����Ŀ¼,����֮�����ļ����ڻ����ļ��У�  
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					//�ļ���������"."&&�ļ���������".."
					//.��ʾ��ǰĿ¼
					//..��ʾ��ǰĿ¼�ĸ�Ŀ¼
					//�ж�ʱ�����߶�Ҫ���ԣ���Ȼ�����޵ݹ�������ȥ�ˣ�
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						subfiles=listFiles(p.assign(dirRoot).append("/").append(fileinfo.name));
				}
				//�������,�����б�  
				else
				{
					subfiles.push_back(p.assign(dirRoot).append("/").append(fileinfo.name));
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			//_findclose������������

			_findclose(hFile);
			return subfiles;
		}

	}


}
