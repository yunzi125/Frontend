#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// 전역 변수 설정
Point2f  pts[4], small(10, 10);							// 4개 좌표 및 좌표 사각형 크기
Mat image;												// 입력 영상 

void draw_rect(Mat image)								// 4개 좌표 잇는 사각형 그리기
{
	Rect img_rect(Point(0, 0), image.size());			// 입력영상 크기 사각형
	for (int i = 0; i < 4; i++)
	{
		Rect rect(pts[i] - small, pts[i] + small);		// 좌표 사각형
		rect &= img_rect;								// 교차 영역 계산
		image(rect) += Scalar(70, 70, 70);				// 사각형 영역 밝게 하기
		line(image, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 255), 1);
		rectangle(image, rect, Scalar(255, 255, 0), 1);	// 좌표 사각형 그리기
	}
	imshow("select rect", image);
}

void warp(Mat image)									// 원근 변환 수행 함수
{
	Point2f dst_pts[4] = {								// 목적 영상 4개 좌표
		Point2f(0, 0), Point2f(350, 0),
		Point2f(350, 350), Point2f(0, 350)
	};
	Mat dst;
	Mat perspect_mat = getPerspectiveTransform(pts, dst_pts);		// 원근변환 행렬 계산
	warpPerspective(image, dst, perspect_mat, Size(350, 350), INTER_CUBIC);
	imshow("왜곡보정", dst);
}

void  onMouse(int event, int x, int y, int flags, void*)	// 마우스 이벤트 제어
{
	Point curr_pt(x, y);									// 현재 클릭 좌표
	static int check = -1;								// 마우스 선택 좌표번호

	if (event == EVENT_LBUTTONDOWN) {		// 마우스 좌 버튼 
		for (int i = 0; i < 4; i++)
		{
			Rect rect(pts[i] - small, pts[i] + small);	// 좌표 사각형들 선언
			if (rect.contains(curr_pt))  check = i;		// 선택 좌표 사각형 찾기
		}
	}
	if (event == EVENT_LBUTTONUP)
		check = -1;									// 선택 좌표번호 초기화

	if (check >= 0) {									// 좌표 사각형 선택시	
		pts[check] = curr_pt;							// 클릭 좌표를 선택 좌표에 저장
		draw_rect(image.clone());						// 4개 좌표 연결 사각형 그리기
		warp(image.clone());							// 원근 변환 수행
	}
}

int main()
{
	image = imread("../image/perspective_test.jpg", 1);
	CV_Assert(image.data);

	pts[0] = Point2f(100, 100), pts[1] = Point2f(300, 100);	// 4개 좌표 초기화
	pts[2] = Point2f(300, 300), pts[3] = Point2f(100, 300);
	draw_rect(image.clone());									// 좌표 사각형 그리기
	setMouseCallback("select rect", onMouse, 0);				// 콜백 함수 등록
	waitKey(0);
	return 0;
}