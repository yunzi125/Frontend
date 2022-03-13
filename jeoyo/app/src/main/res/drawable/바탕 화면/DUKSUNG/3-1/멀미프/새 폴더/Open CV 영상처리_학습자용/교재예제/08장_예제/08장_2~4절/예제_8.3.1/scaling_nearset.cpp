#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void scaling(Mat  img, Mat& dst, Size size)			// 크기 변경 함수
{
	dst = Mat(size, img.type(), Scalar(0));				// 목적영상 생성
	double ratioY = (double)size.height / img.rows;	// 세로 변경 비율 
	double ratioX = (double)size.width / img.cols;		// 가로 변경 비율 

	for (int i = 0; i < img.rows; i++) {				// 입력영상 순회 – 순방향 사상
		for (int j = 0; j < img.cols; j++)
		{
			int x = (int)(j * ratioX);
			int y = (int)(i * ratioY);
			dst.at<uchar>(y, x) = img.at<uchar>(i, j);
		}
	}
}

void scaling_nearest(Mat  img, Mat& dst, Size size)		// 최근접 이웃 보간 
{
	dst = Mat(size, CV_8U, Scalar(0));
	double ratioY = (double)size.height / img.rows;
	double ratioX = (double)size.width / img.cols;

	for (int i = 0; i < dst.rows; i++) {				// 목적영상 순회 - 역방향 사상
		for (int j = 0; j < dst.cols; j++)
		{
			int x = (int)cvRound(j / ratioY);
			int y = (int)cvRound(i / ratioY);
			dst.at<uchar>(i, j) = img.at<uchar>(y, x);
		}
	}
}

int main()
{
	Mat image = imread("../image/interpolation_test.jpg", 0);
	CV_Assert(image.data);

	Mat dst1, dst2;
	scaling(image, dst1, Size(300, 300));				// 크기변경 - 기본
	scaling_nearest(image, dst2, Size(300, 300));		// 크기변경 – 최근접 이웃

	imshow("image", image);
	imshow("dst1-순방향사상", dst1);
	imshow("dst2-최근접 이웃보간", dst2);

	waitKey();
	return 0;
}