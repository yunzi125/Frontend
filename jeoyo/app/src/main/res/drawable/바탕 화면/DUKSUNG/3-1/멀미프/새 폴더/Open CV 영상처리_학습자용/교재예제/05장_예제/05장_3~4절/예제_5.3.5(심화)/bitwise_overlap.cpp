#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/bit_test.jpg", IMREAD_COLOR);
	Mat logo = imread("../image/logo.jpg", IMREAD_COLOR);
	CV_Assert(image.data && logo.data);			// ����ó��
	Mat logo_th, masks[5], background, foreground, dst;		// ��� ���
	
	threshold(logo, logo_th, 70, 255, THRESH_BINARY); // �ΰ� ���� ����ȭ
	split(logo_th, masks);						// �ΰ��� ä�� �и�

	bitwise_or(masks[0], masks[1], masks[3]);	// ������� ����ũ
	bitwise_or(masks[2], masks[3], masks[3]);
	bitwise_not(masks[3], masks[4]);			// ������ ����ũ

	Point center1 = image.size()/ 2;			// ���� �߽���ǥ
	Point center2 = logo.size() / 2;;			// �ΰ� �߽���ǥ
	Point start = center1 - center2;
	Rect roi(start, logo.size());				// �ΰ� ��ġ�� ���ɿ���

	//��Ʈ���� ����ŷ�� �̿��� ���� ������ ����
	bitwise_and(logo, logo, foreground, masks[3]);
	bitwise_and(image(roi), image(roi), background, masks[4]);

	add(background, foreground, dst);			// �ΰ� ����� ��� �ռ�
	dst.copyTo(image(roi));						// �ΰ� �ռ� ������ ���ɿ����� ����

	imshow("background", background);
	imshow("foreground", foreground);
	imshow("dst", dst);
	imshow("image", image);
	waitKey();
	return 0;
}