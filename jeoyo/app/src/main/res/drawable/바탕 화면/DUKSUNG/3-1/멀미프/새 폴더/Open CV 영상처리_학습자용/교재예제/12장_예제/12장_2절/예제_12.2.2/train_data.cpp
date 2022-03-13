#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void  read_trainData(string fn, Mat & trainingData, Mat & lables = Mat())
{
	FileStorage fs(fn, FileStorage::READ);
	CV_Assert(fs.isOpened());

	fs["TrainingData"] >> trainingData;
	fs["classes"] >> lables;
	fs.release();

	trainingData.convertTo(trainingData, CV_32FC1);
}

Ptr<ml::SVM>  SVM_create(int type, int max_iter, double epsilon)
{
	Ptr<ml::SVM> svm = ml::SVM::create();		// SVM ��ü ����
	// SVM �Ķ���� ����
	svm->setType(ml::SVM::C_SVC);				// C-Support Vector Classification				
	svm->setKernel(ml::SVM::LINEAR);			// ���� SVM 
	svm->setGamma(1);							// Ŀ���Լ��� ������
	svm->setC(1);								// ����ȭ�� ���� C �ĸ�����

	TermCriteria criteria(type, max_iter, epsilon);
	svm->setTermCriteria(criteria);				// �ݺ� �˰����� ����
	return svm; 
}


int main()
{
	Mat  trainingData, labels;
	read_trainData("../SVMDATA.xml", trainingData, labels);

	// SVM ��ü ���� 
	Ptr<ml::SVM> svm = SVM_create(CV_TERMCRIT_ITER, 1000, 0 );
	svm->train(trainingData, ml::ROW_SAMPLE, labels);	// �н�����
	svm->save("../SVMtrain.xml");

	return 0;
}