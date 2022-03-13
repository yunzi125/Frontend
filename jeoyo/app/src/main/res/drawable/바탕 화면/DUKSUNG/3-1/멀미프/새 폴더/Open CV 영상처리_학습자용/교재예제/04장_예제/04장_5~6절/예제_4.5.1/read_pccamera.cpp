#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// ���ڿ� ��� �Լ� - �׸��� ȿ�� 
void put_string(Mat &frame, string text, Point pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_SIMPLEX;
	putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);		// �׸��� ȿ�� 	
	putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);// �ۼ� ����
}

int main()
{
	VideoCapture  capture(0);
	if (!capture.isOpened())
	{
		cout << "ī�޶� ������� �ʾҽ��ϴ�." << endl;
		exit(1);
	}
	cout << "�ʺ� " << capture.get(CAP_PROP_FRAME_WIDTH) << endl;
	cout << "���� " << capture.get(CAP_PROP_FRAME_HEIGHT) << endl;
	cout << "���� " << capture.get(CAP_PROP_EXPOSURE) << endl;
	cout << "��� " << capture.get(CAP_PROP_BRIGHTNESS) << endl;
	
	for (;;) {
		Mat frame;
		capture.read(frame);

		put_string(frame, "EXPOS: ", Point(10, 40), capture.get(CAP_PROP_EXPOSURE));

		imshow("ī�޶� ���󺸱�", frame);
		if (waitKey(30) >= 0) break;
	}
	return 0;
}