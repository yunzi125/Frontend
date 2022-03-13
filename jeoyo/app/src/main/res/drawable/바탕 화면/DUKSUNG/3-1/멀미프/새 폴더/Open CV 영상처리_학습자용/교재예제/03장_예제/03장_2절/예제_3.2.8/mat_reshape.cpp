#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void print_matInfo(string m_name, Mat m)
{
	cout << "[ " << m_name << " 행렬]" << endl;
	cout << "    채널수  = " << m.channels() << endl;
	cout << "    행 x 열 = " << m.rows << " x " << m.cols << endl << endl;
}

int main()
{
	Mat m1(2, 6, CV_8U);
	Mat m2 = m1.reshape(2);
	Mat m3 = m1.reshape(3, 2);

	print_matInfo("m1(2, 6)", m1);
	print_matInfo("m2 = m1_reshape(2)", m2);
	print_matInfo("m3 = m1_reshape(3, 2)", m3);

	m1.create(3, 5, CV_16S);
	print_matInfo("m1.create(3, 5)", m1);
	return  0;
}