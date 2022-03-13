#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/bright.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat dst1 = image + 100;
	Mat dst2 = image - 100;
	Mat dst3 = 255 - image;

	Mat dst4(image.size(), image.type());
	Mat dst5(image.size(), image.type());

	for (int i = 0; i < image.rows; i++){
		for (int j = 0; j < image.cols; j++)
		{
			dst4.at<uchar>(i, j) = image.at<uchar>(i, j) + 100;
		//		dst4.at<uchar>(i, j) = saturate_cast<uchar>(image.at<uchar>(i, j) + 100);
			dst5.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
		}
	}

	imshow("�� ����", image);
	imshow("dst1 - ���", dst1);
	imshow("dst2 - ��Ӱ�", dst2);
	imshow("dst3 - ����", dst3);
	imshow("dst4 - ���", dst4);
	imshow("dst5 - ����", dst5);
	waitKey();
	return 0;
}