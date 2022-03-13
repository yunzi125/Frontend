#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/contrast_test.jpg", 0);	// 명암도 타입 읽기
	CV_Assert(image.data);								// 예외처리

	Scalar avg = mean(image) / 2.0;					// 원본 영상 화소 평균의 절반
	Mat dst1 = image * 0.5;							// 명암대비 감소
	Mat dst2 = image * 2.0;							// 명암대비 증가
	Mat dst3 = image * 0.5 + avg[0];				// 영상 평균 이용 대비 감소
	Mat dst4 = image * 2.0 - avg[0];					// 영상 평균 이용 대비 중가

	imshow("image", image);
	imshow("dst1-대비감소", dst1), imshow("dst2-대비증가", dst2);
	imshow("dst3-평균이용 대비감소", dst3), imshow("dst4-평균이용 대비증가", dst4);

	waitKey();
	return 0;
}