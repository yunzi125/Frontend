#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void collect_trainImage(Mat& trainingData, Mat& labels, int Nimages = 140)
{
	for (int i = 0; i< Nimages; i++)
	{
		string fname = format("../image/train/%03d.png", i);// 학습영상 파일
		Mat img = imread(fname, 0);
		CV_Assert(img.data);

		Mat tmp = img.reshape(1, 1);
		int label = (i < 70) ? 1 : 0;

		trainingData.push_back(tmp);
		labels.push_back(label);
	}
	trainingData.convertTo(trainingData, CV_32FC1);
}

void write_traindata(string fn, Mat trainingData, Mat classes)
{
	FileStorage fs(fn, FileStorage::WRITE);
	fs << "TrainingData" << trainingData;
	fs << "classes" << classes;
	fs.release();
}

// xml 데이터 읽기
void  read_trainData(string fn, Mat & trainingData, Mat & lables = Mat())
{
	FileStorage fs(fn, FileStorage::READ);
	CV_Assert(fs.isOpened());

	fs["TrainingData"] >> trainingData;
	fs["classes"] >> lables;
	fs.release();

	trainingData.convertTo(trainingData, CV_32FC1);
}


void main()
{
	Mat trainingData, labels;
//	read_trainData("../SVMDATA.xml", trainingData, labels);
	collect_trainImage(trainingData, labels);
	write_traindata("../SVMDATA.xml", trainingData, labels);
}

