#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/color.jpg", IMREAD_COLOR);
	CV_Assert(image.data);

	Mat bgr[3];
	split(image, bgr);

	imshow("image", image);
	imshow("blue 채널", bgr[0]);
	imshow("green 채널", bgr[1]);
	imshow("red 채널", bgr[2]);

	waitKey(0);
	return 0;
}