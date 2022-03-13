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
	Ptr<ml::SVM> svm = ml::SVM::create();		// SVM 객체 선언
	// SVM 파라미터 지정
	svm->setType(ml::SVM::C_SVC);				// C-Support Vector Classification				
	svm->setKernel(ml::SVM::LINEAR);			// 선형 SVM 
	svm->setGamma(1);							// 커널함수의 감마값
	svm->setC(1);								// 최적화를 위한 C 파리미터

	TermCriteria criteria(type, max_iter, epsilon);
	svm->setTermCriteria(criteria);				// 반복 알고리즘의 조건
	return svm; 
}


int main()
{
	Mat  trainingData, labels;
	read_trainData("../SVMDATA.xml", trainingData, labels);

	// SVM 객체 선언 
	Ptr<ml::SVM> svm = SVM_create(CV_TERMCRIT_ITER, 1000, 0 );
	svm->train(trainingData, ml::ROW_SAMPLE, labels);	// 학습수행
	svm->save("../SVMtrain.xml");

	return 0;
}