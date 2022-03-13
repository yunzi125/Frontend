#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/bit_test.jpg", IMREAD_COLOR);
	Mat logo = imread("../image/logo.jpg", IMREAD_COLOR);
	CV_Assert(image.data && logo.data);			// 예외처리
	Mat logo_th, masks[5], background, foreground, dst;		// 결과 행렬
	
	threshold(logo, logo_th, 70, 255, THRESH_BINARY); // 로고 영상 이진화
	split(logo_th, masks);						// 로고영상 채널 분리

	bitwise_or(masks[0], masks[1], masks[3]);	// 전경통과 마스크
	bitwise_or(masks[2], masks[3], masks[3]);
	bitwise_not(masks[3], masks[4]);			// 배경통과 마스크

	Point center1 = image.size()/ 2;			// 영상 중심좌표
	Point center2 = logo.size() / 2;;			// 로고 중심좌표
	Point start = center1 - center2;
	Rect roi(start, logo.size());				// 로고가 위치할 관심영역

	//비트곱과 마스킹을 이용한 관심 영역의 복사
	bitwise_and(logo, logo, foreground, masks[3]);
	bitwise_and(image(roi), image(roi), background, masks[4]);

	add(background, foreground, dst);			// 로고 전경과 배경 합성
	dst.copyTo(image(roi));						// 로고 합성 영상을 관심영역에 복사

	imshow("background", background);
	imshow("foreground", foreground);
	imshow("dst", dst);
	imshow("image", image);
	waitKey();
	return 0;
}