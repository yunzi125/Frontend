#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image(200, 300, CV_8UC1, Scalar(255));
	namedWindow("키보드 이벤트", WINDOW_AUTOSIZE);
	imshow("키보드 이벤트", image);

	while (1)
	{
		int key = waitKey(100);
		if (key == 27)  break;

		switch (key)
		{
		case 'a':	 cout << "a키 입력" << endl; break;
		case 'b':	 cout << "b키 입력" << endl; break;
		case 0x41:	 cout << "A키 입력" << endl; break;
		case 66:	 cout << "B키 입력" << endl; break;

		case 0x250000:  cout << "왼쪽 화살표키 입력" << endl; break;
		case 0x260000:  cout << "윗쪽 화살표키 입력" << endl; break;
		case 0x270000:  cout << "오른쪽 화살표키 입력" << endl; break;
		case 0x280000:  cout << "아래쪽 화살표키 입력" << endl; break;
		}
	}
	return 0;
}

