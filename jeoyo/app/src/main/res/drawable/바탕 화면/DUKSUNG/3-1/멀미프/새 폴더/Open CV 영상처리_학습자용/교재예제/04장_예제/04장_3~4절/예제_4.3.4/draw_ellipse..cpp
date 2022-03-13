#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Scalar orange(0, 165, 255), blue(255, 0, 0), magenta(255, 0, 255);
	Mat image(300, 700, CV_8UC3, Scalar(255, 255, 255));
	
	Point pt1(120, 150) , pt2(550, 150);
	circle(image, pt1, 1, Scalar(0), 1);
	circle(image, pt2, 1, Scalar(0), 1);

	ellipse(image, pt1, Size(100, 60), 0,  0, 360, orange, 2);
	ellipse(image, pt1, Size(100, 60), 0, 30, 270, blue, 4);

	ellipse(image, pt2, Size(100, 60), 30, 0, 360, orange, 2);
	ellipse(image, pt2, Size(100, 60), 30, -30, 160, magenta, 4);

	imshow("타원 및 호 그리기", image);
	waitKey(0);
	return 0;
}