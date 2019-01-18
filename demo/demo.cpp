


/**
这个类用来测试手写识别效果
注意样本文件保存路径
**/

#include "NumberRec.h"
#define window_name "window"
#define window_name_dst "window_dst"
#define window_name_th "window_th"
#define location_save "/Users/wangzy/study/opencv_300/my_data/%ld.png"

//画笔大小
int pen_width = 10;
int line_type = 3;

//窗口大小
int window_width = 128;
int window_height = 128;
char getResult(float ft);

void on_MouseHandle(int event, int x, int y, int flags, void* param);


bool g_bDrawingBox = false;
RNG g_rng(12345);



int main(int argc, const char * argv[]) {



	Mat srcImage(window_width, window_height, CV_8UC1), tempImage;

	srcImage.copyTo(tempImage);

	namedWindow(window_name);

	setMouseCallback(window_name, on_MouseHandle, (void*)&srcImage);
	
	

	cout << "初始化数据" << endl;
	NumberRec::init();
	cout << "初始化数据完成" << endl;
	cout << "手写识别Menu:" << endl;
	cout << "按C清除画板:" << endl;
	cout << "按S识别手写结果:" << endl;
	cout << "按+画笔加粗:" << endl;
	cout << "按-画笔变细:" << endl;
	cout << "按Q退出" << endl;

	bool start = true;
		while (start){




		srcImage.copyTo(tempImage);

		imshow(window_name, tempImage);

		char key = waitKey();
		switch (key) {
		case 'q':
			cout << "即将关闭" << endl;
			start = false;
			break;
		case 'c':
			cout << "点击了c" << endl;
			srcImage = Scalar::all(0);
			break;
		case '+':
			cout << "点击了+" << endl;
			pen_width += 5;
			break;

		case '-':
			cout << "点击了-" << endl;
			pen_width -= 5;
			if (pen_width<5){
				pen_width = 5;
			}
			break;
		case 's':
			cout << "点击了s" << endl;
			char saved_name[100];


			sprintf(saved_name, location_save, Tool::getTimeLabel());

			vector<vector<Point>> contours;

			srcImage.copyTo(tempImage);


			// find
			findContours(tempImage, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);//识别轮廓

			
			//得到外接矩形
			Rect rect;
			for (size_t i = 0; i != contours.size(); ++i){

				Rect  tempRect = boundingRect(contours[i]);
				//find max rect
				if (tempRect.width>rect.width && tempRect.height>rect.height){
					rect = tempRect;
				}

			}


			Mat resultCenter = Mat(window_width, window_height, CV_8UC1);
			resultCenter = Scalar::all(0);

			Mat tempArea;

			srcImage(rect).copyTo(tempArea);


			Rect resultRIORect;

			int nlt = window_width / 2 - rect.width / 2;
			int nll = window_height / 2 - rect.height / 2;


			//把内容区域拷贝到新图像的中间

			Rect nrect;

			nrect.x = nlt;
			nrect.y = nll;

			nrect.width = rect.width;
			nrect.height = rect.height;



			tempArea.copyTo(resultCenter(nrect));
			Tool::drawRectangle(srcImage, rect);//画出外接矩形
			imshow(window_name, srcImage);

			//                imwrite(saved_name, resultCenter);

			float response = NumberRec::predicatImg(resultCenter);//调用训练结果
			char result = getResult(response);
			cout << "result:" << result << endl;
		



			CvFont  font1;

			char ret[64];
			sprintf(ret, "rec:%c", result);

			putText(srcImage,ret, Point(0, 20), CV_FONT_HERSHEY_PLAIN, 1, Scalar(255, 100, 100));
			imshow(window_name, srcImage);

			//                putText(srcImage, ret, Point(0,0), font1, 4, Scalar(255,200,100));

			//              srcImage=Scalar::all(0);

			break;

		}
		

		if (waitKey(10) == 27)
			break;
	}

	return 0;
}

char getResult(float ft){
	int x = ft;
	switch (x)
	{
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 10:
			return 'A';
	case 11:
		return 'B';
	default:
		return '-1';
	}

}




Point lastPoint(-1, -1);

bool isPress = false;

void on_MouseHandle(int event, int x, int y, int flags, void* param){


	Mat& image = *(Mat*)param;

	switch (event) {

	case EVENT_MOUSEMOVE:

		if (lastPoint.x == -1){
			lastPoint.x = x;
			lastPoint.y = y;
		}
		else{
			if (isPress){
				Point nowPoint(x, y);
				line(image, lastPoint, nowPoint, Scalar(255, 255, 255), pen_width, line_type);
				imshow(window_name, image);
				lastPoint = nowPoint;
			}

		}

		break;

	case EVENT_LBUTTONDOWN:
		isPress = true;
		lastPoint.x = x;
		lastPoint.y = y;
		break;

	case EVENT_LBUTTONUP:
		isPress = false;
		break;
	}

}
