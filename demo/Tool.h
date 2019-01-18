
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
		time_t tt = time(NULL);//这句返回的只是一个时间戳
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
	以引用的方式得到目录下所以文件
	*/
	void getFiles(string path, vector<string>& files)
	{
		//文件句柄  
		long   hFile = 0;
		//文件信息，声明一个存储文件信息的结构体  
		struct _finddata_t fileinfo;
		string p;//字符串，存放路径
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//若查找成功，则进入
		{
			do
			{
				//如果是目录,迭代之（即文件夹内还有文件夹）  
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					//文件名不等于"."&&文件名不等于".."
					//.表示当前目录
					//..表示当前目录的父目录
					//判断时，两者都要忽略，不然就无限递归跳不出去了！
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
				//如果不是,加入列表  
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			//_findclose函数结束查找
			_findclose(hFile);
		}
	}

	/*
	*得到目录下所有文件
	*
	*/
	vector<string> listFiles(string dirRoot){
		
		vector<string> subfiles;
		//文件句柄  
		long   hFile = 0;
		//文件信息，声明一个存储文件信息的结构体  
		struct _finddata_t fileinfo;
		string p;//字符串，存放路径
		if ((hFile = _findfirst(p.assign(dirRoot).append("/*").c_str(), &fileinfo)) != -1)//若查找成功，则进入
		{
			do
			{
				//如果是目录,迭代之（即文件夹内还有文件夹）  
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					//文件名不等于"."&&文件名不等于".."
					//.表示当前目录
					//..表示当前目录的父目录
					//判断时，两者都要忽略，不然就无限递归跳不出去了！
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						subfiles=listFiles(p.assign(dirRoot).append("/").append(fileinfo.name));
				}
				//如果不是,加入列表  
				else
				{
					subfiles.push_back(p.assign(dirRoot).append("/").append(fileinfo.name));
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			//_findclose函数结束查找

			_findclose(hFile);
			return subfiles;
		}

	}


}
