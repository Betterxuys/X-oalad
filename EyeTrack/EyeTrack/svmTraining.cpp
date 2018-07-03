#include "stdafx.h"

using namespace cv;
using namespace cv::ml;
using namespace std;

const int ns = 100;//ns: Number of Samples.
const int npix = 18;//npix: Number of PIXels per picture;

/*README:
��Ҫ��ѵ�����ݼ���ʽ
1.�ļ�data_training.txt:���ڴ洢ѵ�����ݡ�ÿ��һ��sample,ÿ��һ������ֵ��RGB���������ܹ�18��
2.�ļ�data_labels.txt:���ڴ洢������Ӧ���������ÿ��һ��label�����ÿո������
ѵ�������
�ļ�model_svm.xml,�洢��ѵ���õ�ģ��
*/

void svmTraining()
{
	//��ȡlabel�ļ�
	ifstream data_labels;
	data_labels.open("data_labels.txt", ios::in);
	float labels[ns];
	int i;
	float label;
	i = 0;
	while (!data_labels.eof()) {
		data_labels >> label;
		labels[i] = label;
		i++;
	}

	data_labels.close();

	// ��ȡ�����ļ�
	ifstream data_training;
	data_training.open("data_training.txt", ios::in);
	float data[ns][npix];
	int j;
	i = j = 0;
	float pixel;
	while (!data_training.eof()) {
		for (int j = 0; j < npix; j++) {
			data_training >> pixel;
			data[i][j] = pixel;
		}
		i++;
	}

	data_training.close();



	// ����ѵ������
	Mat labelsMat(ns, 1, CV_32SC1, labels);
	Mat trainingDataMat(ns, npix, CV_32FC3, data);//note: Ĭ��channel=3,��ͼƬ��ÿ�����ص���RGB���������

	Ptr<SVM> model = SVM::create();
	model->setType(SVM::C_SVC);
	model->setKernel(SVM::LINEAR);
	model->setGamma(1);
	model->setC(1);
	model->setCoef0(0);
	model->setNu(0);
	model->setP(0);
	model->setTermCriteria(TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 2000, 0.0001));//TermCriteria(type,max_iter,epsilon)
	model->train(trainingDataMat, ROW_SAMPLE, labelsMat);

	//ѵ������ 
	Ptr<TrainData> tData = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
	model->trainAuto(tData, 10);
	model->save("svm_model.xml");
}


