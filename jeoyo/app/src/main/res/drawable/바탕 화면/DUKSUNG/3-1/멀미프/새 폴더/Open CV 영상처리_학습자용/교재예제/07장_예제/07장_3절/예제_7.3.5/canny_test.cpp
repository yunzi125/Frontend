#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int th = 50;						// ĳ�� ���� ���� �Ӱ谪
Mat image, gray, edge;

void onTrackbar(int, void*)								// Ʈ���� �ݹ� �Լ�
{
	GaussianBlur(gray, edge, Size(3, 3), 0.7);			// ����þ� ����
	Canny(edge, edge, th, th * 2, 3);					// ĳ�Ͽ��� ����

	Mat color_edge;
	image.copyTo(color_edge, edge);						// ���� ������ ����
	imshow("�÷� ����", color_edge);
}

int main()
{
	image = imread("../image/smoothing.jpg", 1);		// �÷� ���� �ε�
	CV_Assert(image.data);								// ���� ó��
	cvtColor(image, gray, COLOR_BGR2GRAY);				// ��ϵ� ��ȯ

	namedWindow("�÷� ����", 1);
	createTrackbar("Canny th", "�÷� ����", &th, 100, onTrackbar);
	onTrackbar(th, 0);									// Ʈ���� �Լ� ȣ��

	waitKey(0);
	return 0;
}