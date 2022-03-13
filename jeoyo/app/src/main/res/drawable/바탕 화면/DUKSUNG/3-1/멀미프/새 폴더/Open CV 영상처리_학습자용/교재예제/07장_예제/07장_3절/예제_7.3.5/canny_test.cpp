#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int th = 50;						// 캐니 에지 낮은 임계값
Mat image, gray, edge;

void onTrackbar(int, void*)								// 트렉바 콜백 함수
{
	GaussianBlur(gray, edge, Size(3, 3), 0.7);			// 가우시안 블러링
	Canny(edge, edge, th, th * 2, 3);					// 캐니에지 수행

	Mat color_edge;
	image.copyTo(color_edge, edge);						// 에지 영역만 복사
	imshow("컬러 에지", color_edge);
}

int main()
{
	image = imread("../image/smoothing.jpg", 1);		// 컬러 영상 로드
	CV_Assert(image.data);								// 예외 처리
	cvtColor(image, gray, COLOR_BGR2GRAY);				// 명암도 변환

	namedWindow("컬러 에지", 1);
	createTrackbar("Canny th", "컬러 에지", &th, 100, onTrackbar);
	onTrackbar(th, 0);									// 트랙바 함수 호출

	waitKey(0);
	return 0;
}