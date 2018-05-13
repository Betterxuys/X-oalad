#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#pragma comment(lib,"opencv_world341.lib")

using namespace cv;
using namespace std;
//ȥ���������д���ע��֮��Ϳ��Բ���������Ĵ����м���cv::��std::
//cv::ΪOpenCV�ĺ�����
//std::ΪC++�ı�׼������

int DetectEye(Mat src) {
	cv::Mat gray, equalize, dst;
	//int x[]
	//const char* filename = "1.jpg";
		//cv::imread(filename).copyTo(src);//���Ƶ�src��
	if (src.empty()) {
		throw("Faild open file.");
	}

	cvtColor(src, gray, cv::COLOR_RGB2GRAY);//��ɫ�ռ�ת��RGB<->GREY
	equalizeHist(gray, equalize); //ֱ��ͼ���⻯���ú����ܹ�һ��ͼ�����Ⱥ���ǿ�Աȶ�

	//cv::CascadeClassifier objDetector("D:\\program files\\opencv\\build\\etc\\haarcascades\\haarcascade_eye.xml");
	cv::CascadeClassifier objDetector("D:\\program files\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");
	//������ʶ��һ�������������ļ��仯��
	//�������˵��������������
	std::vector<cv::Rect> objs;
	objDetector.detectMultiScale(equalize, objs, 1.2, 2, CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

	src.copyTo(dst);
	std::vector<cv::Rect>::const_iterator it = objs.begin();
	for (it =objs.begin() ; it != objs.end(); ++it) {
		rectangle(dst, cv::Point(it->x, it->y),
			cv::Point(it->x + it->width, it->y + it->height),
			cv::Scalar(0, 0, 255), 2, CV_AA);
		printf("it=%d\n", it);
		printf("x=%d\ny=%d\nwidth=%d\nheight=%d\n", it->x, it->y, it->width, it->height);
	}
	cv::imshow("src", src);
	cv::imshow("dst", dst);
		//IplImage* pic = cvLoadImage("1.jpg");
		IplImage temp = IplImage(src);
		IplImage* pic = &temp;
		printf("sfesf");
		//int x = 100;
		//int y = 100;
		//int width = 200;
		//int height = 200;
		//CvScalar s = cvScalar(0, 150, 100);
		for (it = objs.begin(); it != objs.end(); it++) {
			//it--;
			printf("x=%d\ny=%d\nwidth=%d\nheight=%d\n", it->x, it->y, it->width, it->height);
			cvSetImageROI(pic, cvRect(it->x, it->y, it->width, it->height));
			IplImage* Dst = cvCreateImage(
				cvSize(it->width, it->height),
				pic->depth,
				pic->nChannels
			);
			cvCopy(pic, Dst, NULL);
			/*cvAddS(pic,s,pic);*/
			cvResetImageROI(pic);
			cvNamedWindow("test");
			cvShowImage("test", Dst);

			//cv::waitKey();
		}
}

int main()
{
	//���µķ�����������У�ֱ�Ӱ�ǰͷ��ע��ȥ������
	//���д����ʱ����ĵ�filename��ĵ�ַ
	//�ҵ�opencv�ǰ�װ��C��Ŀ¼��
	//һЩĿ¼��ַ�������޸�һ��
	bool stop = false;
	Mat frame;
	//DetectEye();//ͼ���۾�ʶ��
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		printf("cap open failed\n");
	}
	while (!stop) {
		cap >> frame;
		DetectEye(frame);
		if (waitKey(30) >= 0) {
			stop = true;
		}
	}
	return 0;
}