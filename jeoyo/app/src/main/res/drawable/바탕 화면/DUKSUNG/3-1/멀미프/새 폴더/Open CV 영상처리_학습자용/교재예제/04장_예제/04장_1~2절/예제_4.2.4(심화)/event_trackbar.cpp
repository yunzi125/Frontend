#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string  title = "밝기변경",  bar_name = "밝기값";		// 전역변수 선언
Mat  image;

void onChange(int  value, void*  userdata)
{
	int  add_value = value - 130;
	cout << "추가 화소값 " << add_value << endl;

	Mat tmp = image + add_value;
	imshow(title, tmp);
}

void onMouse(int event, int x, int y, int flags, void * param)
{
	if (event == EVENT_RBUTTONDOWN) {
		add(image, 10, image);
		setTrackbarPos(bar_name, title, image.at<uchar>(0));
		imshow(title, image);
	}
	else if (event == EVENT_LBUTTONDOWN) {
		subtract(image, 10, image);
		setTrackbarPos(bar_name, title, image.at<uchar>(0));
		imshow(title, image);
	}
}

int main()
{
	int  value = 130;
	image = Mat(300, 400, CV_8UC1, Scalar(120));

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar(bar_name, title, &value, 255, onChange);
	setMouseCallback(title, onMouse, 0);

	imshow(title, image);
	waitKey(0);
	return 0;
}