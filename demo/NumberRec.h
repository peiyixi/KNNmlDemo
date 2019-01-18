


#include "Tool.h"
#include "ImageTool.h"

namespace NumberRec {


	Mat dataMat;//���е���������
	Mat labelMat;//���������������


	Ptr<KNearest> knn;
	//ѧϰ��ʼ��
	void init(){



		//=======================��һ����ʼ=================================

	  	  //��������·��
		string dataRoot = "F:/Tools/MachineLearn/demo/data/��������";

		cout << "ע����������ļ�����·��,��ǰ·��Ϊ��" << endl;

		cout << dataRoot << endl;
		cout << "��һ��:�ɼ�����===========================" << endl;

		vector<string> fs = Tool::listFiles(dataRoot);



		char fn[1024];

		for (int i = 0; i<12; i++){

			sprintf(fn, "%s/%d/", dataRoot.c_str(), i);
			        cout<<fn<<endl;
			vector<string> datas = Tool::listFiles(fn);//����Ŀ¼�ļ���


			for (string data : datas){

				string absPath = data;
				vector<float> hogs = ImageTool::getHog(absPath);//�õ�ָ��ͼƬ��Hog����

				Mat tempMat(1, (int)hogs.size(), CV_32F);

				for (int i = 0, isize = (int)hogs.size(); i<isize; i++){
					tempMat.at<float>(0, i) = hogs.at(i);
				}
				labelMat.push_back(i);      //���ݱ�ǩ

				dataMat.push_back(tempMat); //��������

			}
		}

		//=======================��һ������=================================
		//=======================�ڶ�����ʼ=================================


		cout << "�ڶ���:����Opencv API ��װ����===========================" << endl;

		knn = KNearest::create();  //����knn������
		knn->setDefaultK(5);//�趨kֵ
		knn->setIsClassifier(true);
		Ptr<TrainData> tData = TrainData::create(dataMat, ROW_SAMPLE, labelMat);


		//��ʼѧϰ
		knn->train(tData);
		//=======================�ڶ�������=================================

		//=======================��������ʼ=================================



	}

	float predicatImg(Mat inputMat) {

		if (dataMat.rows == 0){

			cout << "����ʶ��֮ǰ�����ȵ���init��ʼ��" << endl;
			return -1;
		}


		Mat mat = ImageTool::getHogFromMat(inputMat);//�õ�����ͼ���hog����


		float response = knn->predict(mat);//����ѵ���õ�knn������


		return response;


	}

}
