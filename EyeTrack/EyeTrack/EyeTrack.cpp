#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
//#pragma comment(lib,"opencv_world341.lib")
//#pragma comment(lib,"opencv_world341d.lib")

using namespace cv;
using namespace std;
//去掉以上两行代码注释之后就可以不用在下面的代码中加上cv::和std::
//cv::为OpenCV的函数库
//std::为C++的标准函数库

Mat DetectEye(Mat src) {
	cv::Mat gray, equalize, dst;
	if (src.empty()) {
		throw("Faild open file.");
	}

	cvtColor(src, gray, cv::COLOR_RGB2GRAY);//颜色空间转换RGB<->GREY
	equalizeHist(gray, equalize); //直方图均衡化，该函数能归一化图像亮度和增强对比度
	//cv::CascadeClassifier objDetector(".\\etc\\haarcascades\\haarcascade_eye.xml");
	cv::CascadeClassifier objDetector("./etc/haarcascades/haarcascade_frontalface_alt.xml");
	//和脸部识别一样，就是特征文件变化了
	//这个函数说明分类器的种类
	std::vector<cv::Rect> objs;
	objDetector.detectMultiScale(equalize, objs, 1.2, 2, CV_HAAR_SCALE_IMAGE, cv::Size(200, 200));
	if (!objs.empty())
	{
		objs[0].y += objs[0].height / 4;
		objs[0].height /= 3;
		objs[0].width /= 2;
		return src(objs[0]);
	}
	return Mat();
}

int main()
{
	//以下的方法如果想运行，直接把前头的注释去掉即可
	//运行代码的时候请改掉filename里的地址
	//我的opencv是安装在C盘目录下
	//一些目录地址请自行修改一下
	//ldeng:所以要使用相对路径而不是绝对路径
	bool stop = false;
	Mat frame;
	//DetectEye();//图像眼睛识别
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		printf("cap open failed\n");
	}

	//cap >> frame;

	int start = clock();

	int i = 0;
	while (!stop) {
		cap >> frame;
		Mat face = DetectEye(frame);
		if (!face.empty()) {
			imshow("winFace", face);
			waitKey();
		}
		i++;
		if (i % 100 == 0)
			cout << i << ": " << clock() - start << endl;
	}
	return 0;
}