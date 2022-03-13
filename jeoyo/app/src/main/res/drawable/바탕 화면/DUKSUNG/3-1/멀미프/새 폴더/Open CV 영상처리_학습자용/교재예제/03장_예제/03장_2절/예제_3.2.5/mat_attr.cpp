#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat m1(4, 3, CV_32FC3);
	cout << "���� �� =" << m1.dims << endl;
	cout << "�� ���� =" << m1.rows << endl;
	cout << "�� ���� =" << m1.cols << endl;
	cout << "��� ũ�� = " << m1.size() << endl << endl;

	cout << "��ü ���� ���� = " << m1.total() << endl;
	cout << "�� ������ ũ�� = " << m1.elemSize() << endl;
	cout << "ä�δ� �� ������ ũ�� = " << m1.elemSize1() << endl << endl;

	cout << "Ÿ�� = " << m1.type() << endl;
	cout << "Ÿ��(ä�μ� | ����) = " << ((m1.channels() - 1) << 3) + m1.depth() << endl;
	cout << "���� = " << m1.depth() << endl;
	cout << "ä�� = " << m1.channels() << endl << endl;

	cout << "step = " << m1.step << endl;
	cout << "step1() = " << m1.step1() << endl;
	return 0;
}