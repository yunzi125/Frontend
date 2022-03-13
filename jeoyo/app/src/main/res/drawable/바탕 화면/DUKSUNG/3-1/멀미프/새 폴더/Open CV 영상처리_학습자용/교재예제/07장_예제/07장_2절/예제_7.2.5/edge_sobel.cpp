#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void differential(Mat image, Mat& dst, float data1[], float data2[])
{
	Mat dst1, mask1(3, 3, CV_32F, data1);
	Mat dst2, mask2(3, 3, CV_32F, data2);

	filter2D(image, dst1, CV_32F, mask1);		// OpenCV 제공 회선 함수
	filter2D(image, dst2, CV_32F, mask2);
	magnitude(dst1, dst2, dst);
	dst.convertTo(dst, CV_8U);

	convertScaleAbs(dst1, dst1);				// 절대값 및 형변환 동시 수행 함수
	convertScaleAbs(dst2, dst2);
	imshow("dst1 - 수직 마스크", dst1);						// 윈도우 행렬 표시
	imshow("dst2 - 수평 마스크", dst2);
}

int main()
{
	Mat image = imread("../image/edge_test1.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	float data1[] = {
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1
	};
	float data2[] = {
		-1, -2, -1,
		0, 0, 0,
		1, 2, 1
	};

	Mat dst, dst3, dst4;
	differential(image, dst, data1, data2);	// 두 방향 소벨 회선 및 크기 계산

											// OpenCV 제공 소벨 에지 계산
	Sobel(image, dst3, CV_32F, 1, 0, 3);		// x방향 미분 - 수직 마스크
	Sobel(image, dst4, CV_32F, 0, 1, 3);		// y방향 미분 - 수평 마스크
	convertScaleAbs(dst3, dst3);				// 절대값 및 uchar 형변환
	convertScaleAbs(dst4, dst4);

	imshow("image", image), 			imshow("소벨에지", dst);
	imshow("dst3-수직_OpenCV", dst3), imshow("dst4-수평_OpenCV", dst4);

	waitKey();
	return 0;
}