#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	VideoCapture capture(0);
	CV_Assert(capture.isOpened());

	double fps = 29.97;
	int  delay = cvRound(1000.0 / fps);
	Size size(640, 360);
	int  fourcc = VideoWriter::fourcc('D', 'X', '5', '0');

	capture.set(CAP_PROP_FRAME_WIDTH, size.width);
	capture.set(CAP_PROP_FRAME_HEIGHT, size.height);

	cout << "width x height : " << size << endl;
	cout << "VideoWriterfourcc : " << fourcc << endl;
	cout << "delay : " << delay << endl;
	cout << "fps : " << fps << endl;

	VideoWriter  writer;
	writer.open("../image/video_file.avi", fourcc, fps, size);
	CV_Assert(writer.isOpened());

	for (;;) {
		Mat frame;
		capture >> frame; 		// 카메라 영상받기
		writer << frame; 		// 프레임을 동영상으로 저장
		//writer.write(frame);

		imshow("카메라 영상보기", frame);
		if (waitKey(delay) >= 0)
			break;
	}
	return 0;
}