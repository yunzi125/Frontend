#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat BGR_img = imread("../image/color_space.jpg", 1);
	CV_Assert(BGR_img.data);

	Mat YCC_img, YUV_img, Lab_img, Gray_img;
	cvtColor(BGR_img, Gray_img, CV_BGR2GRAY);
	cvtColor(BGR_img, YCC_img, CV_BGR2YCrCb);
	cvtColor(BGR_img, YUV_img, CV_BGR2YUV);
	cvtColor(BGR_img, Lab_img, CV_BGR2Lab);

	Mat YCC_arr[3], YUV_arr[3], Lab_arr[3];
	split(YCC_img, YCC_arr);
	split(YUV_img, YUV_arr);
	split(Lab_img, Lab_arr);

	imshow("BGR_img", BGR_img) ,		imshow("Gray_img", Gray_img);
	imshow("YCC_arr[0]-Y", YCC_arr[0]),	imshow("YCC_arr[1]-Cr", YCC_arr[1]);
	imshow("YCC_arr[2]-Cb", YCC_arr[2]), imshow("YUV_arr[0]-Y", YUV_arr[0]);
	imshow("YUV_arr[1]-U", YUV_arr[1]),	imshow("YUV_arr[2]-V", YUV_arr[2]);
	imshow("Lab_arr[0]-L", Lab_arr[0]),	imshow("Lab_arr[1]-a", Lab_arr[1]);
	imshow("Lab_arr[2]-b", Lab_arr[2]);
	waitKey(0);
	return 0;
}