#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Matx<uchar, 2, 2> m1;
	Matx<ushort, 2, 2> m2;

	m1(0, 0) = -50;
	m1(0, 1) = 300;
	m1(1, 0) = saturate_cast<uchar>(-50);
	m1(1, 1) = saturate_cast<uchar>(300);

	m2(0, 0) = -50;
	m2(0, 1) = 80000;
	m2(1, 0) = saturate_cast<unsigned short>(-50);
	m2(1, 1) = saturate_cast<unsigned short>(80000);

	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m2] = " << endl << m2 << endl;
	return 0;
}