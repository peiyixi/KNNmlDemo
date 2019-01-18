


#include "Tool.h"
#include "ImageTool.h"

namespace NumberRec {


	Mat dataMat;//所有的样本数据
	Mat labelMat;//样本所代表的数字


	Ptr<KNearest> knn;
	//学习初始化
	void init(){



		//=======================第一步开始=================================

	  	  //样本数据路径
		string dataRoot = "F:/Tools/MachineLearn/demo/data/样本数据";

		cout << "注意你的样本文件保存路径,当前路经为：" << endl;

		cout << dataRoot << endl;
		cout << "第一步:采集数据===========================" << endl;

		vector<string> fs = Tool::listFiles(dataRoot);



		char fn[1024];

		for (int i = 0; i<12; i++){

			sprintf(fn, "%s/%d/", dataRoot.c_str(), i);
			        cout<<fn<<endl;
			vector<string> datas = Tool::listFiles(fn);//遍历目录文件夹


			for (string data : datas){

				string absPath = data;
				vector<float> hogs = ImageTool::getHog(absPath);//得到指定图片的Hog特征

				Mat tempMat(1, (int)hogs.size(), CV_32F);

				for (int i = 0, isize = (int)hogs.size(); i<isize; i++){
					tempMat.at<float>(0, i) = hogs.at(i);
				}
				labelMat.push_back(i);      //数据标签

				dataMat.push_back(tempMat); //数据特征

			}
		}

		//=======================第一步结束=================================
		//=======================第二步开始=================================


		cout << "第二步:调用Opencv API 组装数据===========================" << endl;

		knn = KNearest::create();  //创建knn分类器
		knn->setDefaultK(5);//设定k值
		knn->setIsClassifier(true);
		Ptr<TrainData> tData = TrainData::create(dataMat, ROW_SAMPLE, labelMat);


		//开始学习
		knn->train(tData);
		//=======================第二步结束=================================

		//=======================第三步开始=================================



	}

	float predicatImg(Mat inputMat) {

		if (dataMat.rows == 0){

			cout << "调用识别之前，请先调用init初始化" << endl;
			return -1;
		}


		Mat mat = ImageTool::getHogFromMat(inputMat);//得到传入图像的hog特征


		float response = knn->predict(mat);//调用训练好的knn分类器


		return response;


	}

}
