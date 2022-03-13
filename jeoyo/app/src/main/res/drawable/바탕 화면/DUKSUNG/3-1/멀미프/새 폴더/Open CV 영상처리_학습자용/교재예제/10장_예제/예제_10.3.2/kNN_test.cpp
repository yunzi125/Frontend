#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void make_trainData(Mat trainData, Mat group[2] , Mat& classLable)
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

void kNN_test(Ptr<ml::KNearest>  knn, int K, Mat& image)
{
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++)
		{
			Matx12f sample((float)x, (float)y);
			Mat response;
			knn->findNearest(sample, K, response);

			int resp = (int)response.at<float>(0);
			if (resp == 1)	image.at<Vec3b>(y, x) = Vec3b(0, 180, 0);
			else 			image.at<Vec3b>(y, x) = Vec3b(0, 0, 180);
		}
	}
}

int main()
{
	int Nsample = 100;
	Mat trainData(Nsample, 2, CV_32FC1, Scalar(0));
	Mat classLable(Nsample, 1, CV_32FC1, Scalar(0));
	
	Mat group[2];
	make_trainData(trainData, group, classLable);

	Mat image(400, 400, CV_8UC3, Scalar(255, 255, 255));

	int K = 7;
	Ptr<ml::KNearest>  knn = ml::KNearest::create();
	knn->train(trainData, ml::ROW_SAMPLE, classLable);
	kNN_test(knn, K, image );

	draw_points(image, group);
	imshow("sample K=" + to_string(K), image);
	waitKey();
	return 0;
}