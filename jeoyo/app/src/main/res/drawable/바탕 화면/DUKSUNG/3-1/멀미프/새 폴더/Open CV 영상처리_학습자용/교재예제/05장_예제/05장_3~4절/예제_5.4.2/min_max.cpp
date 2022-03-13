#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	uchar data[] = {
		10, 200, 5, 7, 9,
		15, 35, 60, 80, 170,
		100, 2, 55, 37, 70
	};
	Mat  m1(3, 5, CV_8U, data);
	Mat  m2(3, 5, CV_8U, Scalar(50));
	Mat  m_min, m_max;						// �ּҰ� ���, �ִ밪 ���
	double minVal, maxVal;
	int    minIdx[2] = {}, maxIdx[2] = {};	// �ּҰ� ��ǥ, �ִ밪 ��ǥ
	Point  minLoc, maxLoc;

	min(m1, 30, m_min);						// �� ��� ���Ұ� �ּҰ� ����
	max(m1, m2, m_max);						// �� ��� �ִ밪 ���
	minMaxIdx(m1, &minVal, &maxVal, minIdx, maxIdx);
	minMaxLoc(m1, 0, 0, &minLoc, &maxLoc);

	cout << "[m1] = " << endl << m1 << endl << endl;
	cout << "[m_min] = " << endl << m_min << endl;
	cout << "[m_max] = " << endl << m_max << endl << endl;
	
	cout << "m1 ��� ���� �ּҰ� : " << minVal << endl;
	cout << "    �ּҰ� ��ǥ : " << minIdx[1] << ", " << minIdx[0] << endl;

	cout << "m1 ��� ���� �ִ밪 : " << maxVal << endl;
	cout << "    �ִ밪 ��ǥ : " << maxIdx[1] << ", " << maxIdx[0] << endl << endl;

	cout << "m1 ��� �ּҰ� ��ǥ: " << minLoc << endl;
	cout << "m1 ��� �ִ밪 ��ǥ " << maxLoc << endl;
	return 0;
}






