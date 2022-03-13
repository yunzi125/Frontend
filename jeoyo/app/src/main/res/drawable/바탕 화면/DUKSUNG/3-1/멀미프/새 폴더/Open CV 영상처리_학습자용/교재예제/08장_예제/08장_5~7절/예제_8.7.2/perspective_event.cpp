#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// ���� ���� ����
Point2f  pts[4], small(10, 10);							// 4�� ��ǥ �� ��ǥ �簢�� ũ��
Mat image;												// �Է� ���� 

void draw_rect(Mat image)								// 4�� ��ǥ �մ� �簢�� �׸���
{
	Rect img_rect(Point(0, 0), image.size());			// �Է¿��� ũ�� �簢��
	for (int i = 0; i < 4; i++)
	{
		Rect rect(pts[i] - small, pts[i] + small);		// ��ǥ �簢��
		rect &= img_rect;								// ���� ���� ���
		image(rect) += Scalar(70, 70, 70);				// �簢�� ���� ��� �ϱ�
		line(image, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 255), 1);
		rectangle(image, rect, Scalar(255, 255, 0), 1);	// ��ǥ �簢�� �׸���
	}
	imshow("select rect", image);
}

void warp(Mat image)									// ���� ��ȯ ���� �Լ�
{
	Point2f dst_pts[4] = {								// ���� ���� 4�� ��ǥ
		Point2f(0, 0), Point2f(350, 0),
		Point2f(350, 350), Point2f(0, 350)
	};
	Mat dst;
	Mat perspect_mat = getPerspectiveTransform(pts, dst_pts);		// ���ٺ�ȯ ��� ���
	warpPerspective(image, dst, perspect_mat, Size(350, 350), INTER_CUBIC);
	imshow("�ְ��", dst);
}

void  onMouse(int event, int x, int y, int flags, void*)	// ���콺 �̺�Ʈ ����
{
	Point curr_pt(x, y);									// ���� Ŭ�� ��ǥ
	static int check = -1;								// ���콺 ���� ��ǥ��ȣ

	if (event == EVENT_LBUTTONDOWN) {		// ���콺 �� ��ư 
		for (int i = 0; i < 4; i++)
		{
			Rect rect(pts[i] - small, pts[i] + small);	// ��ǥ �簢���� ����
			if (rect.contains(curr_pt))  check = i;		// ���� ��ǥ �簢�� ã��
		}
	}
	if (event == EVENT_LBUTTONUP)
		check = -1;									// ���� ��ǥ��ȣ �ʱ�ȭ

	if (check >= 0) {									// ��ǥ �簢�� ���ý�	
		pts[check] = curr_pt;							// Ŭ�� ��ǥ�� ���� ��ǥ�� ����
		draw_rect(image.clone());						// 4�� ��ǥ ���� �簢�� �׸���
		warp(image.clone());							// ���� ��ȯ ����
	}
}

int main()
{
	image = imread("../image/perspective_test.jpg", 1);
	CV_Assert(image.data);

	pts[0] = Point2f(100, 100), pts[1] = Point2f(300, 100);	// 4�� ��ǥ �ʱ�ȭ
	pts[2] = Point2f(300, 300), pts[3] = Point2f(100, 300);
	draw_rect(image.clone());									// ��ǥ �簢�� �׸���
	setMouseCallback("select rect", onMouse, 0);				// �ݹ� �Լ� ���
	waitKey(0);
	return 0;
}