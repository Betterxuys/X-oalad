#include "stdafx.h"
using namespace cv;
using namespace std;

Mat resizeAndGray(const Mat img, int width, int height) {
	Mat gray,equalize,small;
	cvtColor(img, gray, cv::COLOR_RGB2GRAY);//��ɫ�ռ�ת��RGB<->GREY
	equalizeHist(gray, equalize); //ֱ��ͼ���⻯���ú����ܹ�һ��ͼ�����Ⱥ���ǿ�Աȶ�
	resize(equalize, small, Size(width, height));
	return small;
}