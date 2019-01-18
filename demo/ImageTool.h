

namespace ImageTool {


	/*
	  cvSize _winSize：窗口大小  
	  cvSize _blockSize：块大小 
	  cvSize _blockStride：块滑动增量
	  cvSize _cellSize：胞元大小
	  int _nbins：梯度方向度
	 */
	
	vector<float> getHog(string path){



		Mat imageMat;
		imageMat = imread(path, 1);//
		HOGDescriptor *hog = new HOGDescriptor(cvSize(128, 128), cvSize(64, 64), cvSize(32, 32), cvSize(32, 32), 9);
		vector<float> descriptors;//得到特征向量
		hog->compute(imageMat, descriptors);


		return descriptors;
	}


	Mat getHotMat(string path){

		vector<float> mats = getHog(path);

		Mat ret(1, (int)mats.size(), CV_32F);


		for (int i = 0, isize = (int)mats.size(); i<isize; i++){

			ret.at<float>(0, i) = mats.at(i);
		}

		return ret;
	}

	//得到传入Mat的Hog特征
	Mat getHogFromMat(Mat inputMat){



		HOGDescriptor *hog = new HOGDescriptor(cvSize(128, 128), cvSize(64, 64), cvSize(32, 32), cvSize(32, 32), 9);//
		vector<float> descriptors;
		hog->compute(inputMat, descriptors);

		Mat ret(1, (int)descriptors.size(), CV_32F);


		for (int i = 0, isize = (int)descriptors.size(); i<isize; i++){

			ret.at<float>(0, i) = descriptors.at(i);
		}

		return ret;


	}


}








