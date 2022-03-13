#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void differential(Mat image, Mat& dst, float data1[], float data2[])
{
	Mat dst1, mask1(3, 3, CV_32F, data1);
	Mat dst2, mask2(3, 3, CV_32F, data2);

	filter2D(image, dst1, CV_32F, mask1);		// OpenCV ���� ȸ�� �Լ�
	filter2D(image, dst2, CV_32F, mask2);
	magnitude(dst1, dst2, dst);
	dst.convertTo(dst, CV_8U);

	convertScaleAbs(dst1, dst1);				// ���밪 �� ����ȯ ���� ���� �Լ�
	convertScaleAbs(dst2, dst2);
	imshow("dst1 - ���� ����ũ", dst1);						// ������ ��� ǥ��
	imshow("dst2 - ���� ����ũ", dst2);
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
	differential(image, dst, data1, data2);	// �� ���� �Һ� ȸ�� �� ũ�� ���

											// OpenCV ���� �Һ� ���� ���
	Sobel(image, dst3, CV_32F, 1, 0, 3);		// x���� �̺� - ���� ����ũ
	Sobel(image, dst4, CV_32F, 0, 1, 3);		// y���� �̺� - ���� ����ũ
	convertScaleAbs(dst3, dst3);				// ���밪 �� uchar ����ȯ
	convertScaleAbs(dst4, dst4);

	imshow("image", image), 			imshow("�Һ�����", dst);
	imshow("dst3-����_OpenCV", dst3), imshow("dst4-����_OpenCV", dst4);

	waitKey();
	return 0;
}