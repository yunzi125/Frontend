#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void make_tranData(Mat trainData, Mat group[2] , Mat& classLable)
{
	int half = trainData.rows / 2;
	Range r1(0, half);
	Range r2(half, trainData.rows);

	group[0] = trainData.rowRange(r1);
	group[1] = trainData.rowRange(r2);

	randn(group[0], 150, 50);
	randn(group[1], 250, 50);
	classLable.rowRange(r1).setTo(0);
	classLable.rowRange(r2).setTo(1);
}


void draw_points(Mat& image, Mat group[2])
{
	for (int i = 0; i < group[0].rows; i++)
	{
		Point2f pt1(group[0].at<float>(i, 0), group[0].at<float>(i, 1));
		Point2f pt2(group[1].at<float>(i, 0), group[1].at<float>(i, 1));
		circle(image, pt1, 3, Scalar(0, 0, 255), FILLED);
		circle(image, pt2, 3, Scalar(0, 255, 0), FILLED);
	}
}

int main()
{
	int Nsample = 100;
	Mat trainData(Nsample, 2, CV_32FC1, Scalar(0));
	Mat classLable(Nsample, 1, CV_32FC1, Scalar(0));
	Mat image(400, 400, CV_8UC3, Scalar(255, 255, 255));

	Mat group[2];
	make_tranData(trainData, group, classLable);
	draw_points(image, group);
	imshow("학습데이터",  image);
	waitKey();
	return 0;
}