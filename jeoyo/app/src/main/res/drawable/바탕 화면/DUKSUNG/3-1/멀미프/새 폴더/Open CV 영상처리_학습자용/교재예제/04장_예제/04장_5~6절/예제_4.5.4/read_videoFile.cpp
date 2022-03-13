#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void put_string(Mat &frame, string text, Point pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_PLAIN;
	putText(frame, text, shade, font, 1.8, Scalar(0, 0, 0), 2);
	putText(frame, text, pt, font, 1.8, Scalar(120, 200, 90), 2);
}

int main()
{
	VideoCapture capture;
	capture.open("../image/video_file.avi");
	CV_Assert(capture.isOpened());

	double frame_rate = capture.get(CV_CAP_PROP_FPS);
	int delay = 1000 / frame_rate;
	int frmae_cnt = 0;
	Mat  frame;

	while (capture.read(frame))
	{
		if (waitKey(delay) >= 0) break;

		if (frmae_cnt < 100);
		else if (frmae_cnt < 200)	frame -= Scalar(0, 0, 100);
		else if (frmae_cnt < 300) 	frame += Scalar(100, 0, 0);
		else if (frmae_cnt < 400)	frame = frame * 1.5;
		else if (frmae_cnt < 500)	frame = frame * 0.5;

		put_string(frame, "frmae_cnt ", Point(20, 50), frmae_cnt++);
		imshow("동영상 파일읽기", frame);
	}
	return 0;
}