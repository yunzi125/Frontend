#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// ���ڿ� ��� �Լ� - �׸��� ȿ�� 
void put_string(Mat &frame, string text, Point pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_SIMPLEX;
	putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);
	putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);
}

VideoCapture capture;				// ���� ���� ����
									
void zoom_bar(int value, void*) {    // Ʈ���� �ݹ� �Լ���
	capture.set(CAP_PROP_ZOOM, value);
}
void focus_bar(int value, void*){
	capture.set(CAP_PROP_FOCUS, value);
}

int main()
{
	capture.open(0);												// 0�� ī�޶� ����
	CV_Assert(capture.isOpened());								// ī�޶� ���� ���� ó��

	capture.set(CAP_PROP_FRAME_WIDTH, 400); 	// ī�޶� ������ ũ�� ����
	capture.set(CAP_PROP_FRAME_HEIGHT, 300);
	capture.set(CAP_PROP_AUTOFOCUS, 0);
	capture.set(CAP_PROP_BRIGHTNESS, 150);

	int zoom = capture.get(CAP_PROP_ZOOM);				// ī�޶� �Ӽ� ��������
	int focus = capture.get(CAP_PROP_FOCUS);

	string title = "ī�޶� �Ӽ�����";							// ������ �̸� ����
	namedWindow(title);										// ������ ����
	createTrackbar("zoom", title, &zoom, 10, zoom_bar); 		// �����쿡 �� Ʈ���� �߰�
	createTrackbar("focus", title, &focus, 40, focus_bar);

	for (;;) {
		Mat frame;
		capture >> frame;										// ī�޶� ����ޱ�

		put_string(frame, "zoom: ", Point(10, 240), zoom);	// �� �� ���� ǥ��
		put_string(frame, "focus: ", Point(10, 270), focus);		// ��Ŀ�� 

		imshow(title, frame);
		if (waitKey(30) >= 0) break;
	}
	return 0;
}