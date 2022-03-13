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
	imshow("blue ä��", bgr[0]);
	imshow("green ä��", bgr[1]);
	imshow("red ä��", bgr[2]);

	waitKey(0);
	return 0;
}