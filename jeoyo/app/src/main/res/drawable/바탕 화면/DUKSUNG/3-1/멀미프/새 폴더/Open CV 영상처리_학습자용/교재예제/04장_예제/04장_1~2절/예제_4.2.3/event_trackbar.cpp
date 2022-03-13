#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string  title = "트랙바 이벤트";
Mat  image;

void onChange(int  value, void*  userdata)
{
	int  add_value = value - 130;
	cout << "추가 화소값 " << add_value << endl;

	Mat tmp = image + add_value;
	imshow(title, tmp);
}

int main()
{
	int  value = 130;
	image = Mat(300, 400, CV_8UC1, Scalar(120));

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("밝기값", title, &value, 255, onChange);

	imshow(title, image);
	waitKey(0);
	return 0;
}