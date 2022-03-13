#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image1(300, 400, CV_8U, Scalar(255));
	Mat image2(300, 400, CV_8U, Scalar(100));
	string  title1 = "white창 제어";
	string  title2 = "gray 창 제어";

	namedWindow(title1, WINDOW_AUTOSIZE);
	namedWindow(title2, WINDOW_NORMAL);
	moveWindow(title1, 100, 200);
	moveWindow(title2, 300, 200);

	imshow(title1, image1);
	imshow(title2, image2);
	waitKey();
	destroyAllWindows();

	return 0;
}