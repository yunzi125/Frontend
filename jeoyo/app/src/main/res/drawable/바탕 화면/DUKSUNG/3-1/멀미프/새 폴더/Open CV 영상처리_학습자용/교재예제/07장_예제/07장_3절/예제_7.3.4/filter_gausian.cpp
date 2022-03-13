#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#include <time.h>

Mat getGaussianMask(Size size, double sigmaX, double sigmaY)
{
	double ratio = 1 / (sigmaX * sigmaY * CV_PI);
	double sigmaX2 = 2 * sigmaX * sigmaX;
	double sigmaY2 = 2 * sigmaY * sigmaY;

	Point center = size / 2;
	Mat mask(size, CV_64F);

	for (int i = 0; i < size.height; i++){
		for (int j = 0; j < size.width; j++)
		{
			int x2 = (j - center.x) * (j - center.x);
			int y2 = (i - center.y) * (i - center.y);
			mask.at<double>(i, j) = ratio * exp(-((x2 / sigmaX2) + (y2 / sigmaY2)));
		}
	}
	return (mask / sum(mask)[0]);
}

int main()
{
	Mat image = imread("../image/smoothing.jpg", 0);
	CV_Assert(image.data);

	Size  size(5, 29);
	double sigmaX = 0.3*((size.width  - 1)*0.5 - 1) + 0.8;
	double sigmaY = 0.3*((size.height - 1)*0.5 - 1) + 0.8;

	Mat gauss_img1, gauss_img2, gauss_img3;
	Mat gaussian_2d = getGaussianMask(size, sigmaX, sigmaY);
	Mat gaussian_1dX = getGaussianKernel(size.width , -1, CV_64F);
	Mat gaussian_1dY = getGaussianKernel(size.height, -1, CV_64F);

	filter2D(image, gauss_img1, -1, gaussian_2d);
	GaussianBlur(image, gauss_img2, size, sigmaX, sigmaY);
	sepFilter2D(image, gauss_img3, -1, gaussian_1dX, gaussian_1dY);

	imshow("image", image);
	imshow("사용자 생성 마스크 적용", gauss_img1);
	imshow("가우시안 블러링 적용 ", gauss_img2);
	imshow("가우시안 계수로 마스크 생성", gauss_img3);

	waitKey();
	return 0;
}