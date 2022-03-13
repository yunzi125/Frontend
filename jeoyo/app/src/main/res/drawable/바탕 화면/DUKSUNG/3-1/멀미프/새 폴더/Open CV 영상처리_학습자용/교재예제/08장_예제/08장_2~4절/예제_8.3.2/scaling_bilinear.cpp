#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void scaling_nearest(Mat  img, Mat& dst, Size size)		// 최근접 이웃 보간 
{
	dst = Mat(size, CV_8U, Scalar(0));
	double ratioY = (double)size.height / img.rows;
	double ratioX = (double)size.width / img.cols;

	for (int i = 0; i < dst.rows; i++) {				// 목적영상 순회 – 역방향 사상
		for (int j = 0; j < dst.cols; j++)
		{
			int x = (int)cvRound(j / ratioY);
			int y = (int)cvRound(i / ratioY);
			dst.at<uchar>(i, j) = img.at<uchar>(y, x);
		}
	}
}

uchar bilinear_value(Mat img, double x, double y)	// 단일 화소 양선형 보간
{
	if (x >= img.cols - 1)  x--;
	if (y >= img.rows - 1)  y--;

	// 4개 화소 가져옴
	Point pt((int)x, (int)y);
	int A = img.at<uchar>(pt);						// 왼쪽상단 화소
	int B = img.at<uchar>(pt + Point(0, 1));		// 왼쪽하단 화소
	int C = img.at<uchar>(pt + Point(1, 0));		// 오른쪽상단 화소
	int D = img.at<uchar>(pt + Point(1, 1));		// 오른쪽하단 화소

	double alpha = y - pt.y;
	double beta = x - pt.x;
	int M1 = A + (int)cvRound(alpha * (B – A));		// 1차 보간
	int M2 = C + (int)cvRound(alpha * (D - C));
	int P = M1 + (int)cvRound(beta * (M2 – M1));		// 2차 보간
	return  saturate_cast<uchar>(P);
}

void scaling_bilinear(Mat  img, Mat& dst, Size size)		// 크기변경 – 양선형 보간
{
	dst = Mat(size, img.type(), Scalar(0));
	double ratio_Y = (double)size.height / img.rows;
	double ratio_X = (double)size.width / img.cols;

	for (int i = 0; i < dst.rows; i++) {		// 목적영상 순회 – 역방향 사상
		for (int j = 0; j < dst.cols; j++) {
			double y = i / ratio_Y;
			double x = j / ratio_X;
			dst.at<uchar>(i, j) = bilinear_value(img, x, y);		// 화소 양선형 보간
		}
	}
}

int main()
{
	Mat image = imread("../image/interpolation_test.jpg", 0);		// 명암도 영상 로드
	CV_Assert(image.data);

	Mat dst1, dst2, dst3, dst4;
	scaling_bilinear(image, dst1, Size(300, 300));		// 크기변경 – 양선형 보간
	scaling_nearest(image, dst2, Size(300, 300));		// 크기변경 – 최근접 보간
	resize(image, dst3, Size(300, 300), 0, 0, INTER_LINEAR); // OpenCV 함수 적용
	resize(image, dst4, Size(300, 300), 0, 0, INTER_NEAREST);

	imshow("image", image);
	imshow("dst1-양선형", dst1), imshow("dst2-최근접이웃", dst2);
	imshow("OpenCV-양선형", dst3), imshow("OpenCV-최근접이웃", dst4);
	waitKey();
	return 0;
}