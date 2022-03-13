#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

uchar bilinear_value(Mat img, double x, double y)
{
	if (x >= img.cols - 1)  x--;
	if (y >= img.rows - 1)  y--;

	// 4개 화소 가져옴
	Point pt((int)x, (int)y);
	int A = img.at<uchar>(pt);
	int B = img.at<uchar>(pt + Point(0, 1));
	int C = img.at<uchar>(pt + Point(1, 0));
	int D = img.at<uchar>(pt + Point(1, 1));

	//1차 보간
	double alpha = y - pt.y;
	double beta = x - pt.x;
	int M1 = A + (int)cvRound(alpha * (B - A));
	int M2 = C + (int)cvRound(alpha * (D - C));

	//2차 보간
	int P = M1 + (int)cvRound(beta * (M2 - M1));
	return  saturate_cast<uchar>(P);
}

void rotation(Mat img, Mat& dst, double dgree)			// 회전 변환 함수
{
	double radian = dgree / 180 * CV_PI;				// 회전각도 - 라디안
	double sin_value = sin(radian);							// 사인 코사인 값 미리 계산
	double cos_value = cos(radian);

	Rect rect(Point(0, 0), img.size());						// 입력 영상 범위 사각형
	dst = Mat(img.size(), img.type(), Scalar(0));			// 목적 영상 

	for (int i = 0; i < dst.rows; i++) {						// 목적영상 순회 – 역방향 사상
		for (int j = 0; j < dst.cols; j++)
		{
			double x = j * cos_value + i * sin_value;	// 회전 변환 수식
			double y = -j * sin_value + i * cos_value;

			if (rect.contains(Point2d(x, y)))				// 계산좌표의 입력 영상 범위 확인
				dst.at<uchar>(i, j) = bilinear_value(img, x, y);		// 화소값 양선형 보간
		}
	}
}

void rotation(Mat img, Mat& dst, double dgree, Point pt)	 // pt 좌표 기준 회전 변환
{
	double radian = dgree / 180 * CV_PI;
	double sin_value = sin(radian);
	double cos_value = cos(radian);

	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++)
		{
			int jj = j - pt.x;							// pt 좌표만큼 평행이동
			int ii = i - pt.y;
			double x = jj * cos_value + ii * sin_value + pt.x;
			double y = -jj * sin_value + ii * cos_value + pt.y;

			if (rect.contains(Point2d(x, y)))
				dst.at<uchar>(i, j) = bilinear_value(img, x, y);
		}
	}
}

int main()
{
	Mat image = imread("../image/rotate_test.jpg", 0);
	CV_Assert(image.data);

	Mat dst1, dst2, dst3, dst4;
	Point center = image.size() / 2;					// 영상 중심 좌표 계산
	rotation(image, dst1, 20);							// 원점 기준 회전변환
	rotation(image, dst2, 20, center);					// 영상 중심 기준 회전변환

	imshow("image", image);
	imshow("dst1-20도 회전(원점)", dst1);
	imshow("dst2-20도 회전(중심점)", dst2);
	waitKey();
	return 0;
}