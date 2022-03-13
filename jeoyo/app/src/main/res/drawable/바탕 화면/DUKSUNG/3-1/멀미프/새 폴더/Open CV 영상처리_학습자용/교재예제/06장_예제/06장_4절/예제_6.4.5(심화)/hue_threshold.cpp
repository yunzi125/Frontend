#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
Range th(50, 100);											// 트랙바로 선택할 범위 변수
Mat hue;													// 색상 채널 전역 번수지정

void onThreshold(int  value, void*  userdata)
{
	Mat result = Mat(hue.size(), CV_8U, Scalar(0));

	// 선택 범위에 이진화 수행
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++)
		{	// 선택 범위에 대한 조건 설정
			bool ck = hue.at<uchar>(i, j) >= th.start && hue.at<uchar>(i, j) < th.end;
			result.at<uchar>(i, j) = (ck) ? 255 : 0;		// 이진값 지정
		}
	}
	imshow("result", result);
}

int main()
{
	Mat BGR_img = imread("../image/color_space.jpg", 1);// 컬러 영상 로드
	CV_Assert(BGR_img.data);

	Mat HSV, hsv[3];
	cvtColor(BGR_img, HSV, CV_BGR2HSV);			// 컬러 공간 변환
	split(HSV, hsv);										// 채널 분리
	hsv[0].copyTo(hue);										// hue 행렬에 색상 채널 복사

	namedWindow("result", WINDOW_AUTOSIZE);
	createTrackbar("Hue_th1", "result", &th.start, 255, onThreshold);	// 트랙바 등록
	createTrackbar("Hue_th2", "result", &th.end, 255, onThreshold);

	onThreshold(0,0);													// 이진화 수행
	imshow("BGR_img", BGR_img);
	waitKey(0);
	return 0;
}