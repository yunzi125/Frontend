#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void testMouse(int, int, int, int, void *);

int main()
{
	Mat image(200, 300, CV_8UC1);
	image.setTo(255);
	imshow("마우스 이벤트1", image);
	imshow("마우스 이벤트2", image);

	setMouseCallback("마우스 이벤트1", testMouse, 0);
	waitKey(0);
	return 0;
}

void testMouse(int event, int x, int y, int flags, void * param)
{
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		cout << "마우스 왼쪽버튼 누르기" << endl;
		break;
	case EVENT_RBUTTONDOWN:
		cout << "마우스 오른쪽버튼 누르기" << endl;
		break;
	case EVENT_RBUTTONUP:
		cout << "마우스 오른쪽버튼 떼기" << endl;
		break;
	case EVENT_LBUTTONDBLCLK:
		cout << "마우스 왼쪽버튼 더블클릭" << endl;
		break;
	}
}