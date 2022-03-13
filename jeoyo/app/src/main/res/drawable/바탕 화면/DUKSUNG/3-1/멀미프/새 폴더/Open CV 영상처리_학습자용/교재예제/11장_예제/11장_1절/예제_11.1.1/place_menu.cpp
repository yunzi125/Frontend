#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 전역변수 설정
vector<Rect> icons;								// 아이콘 사각형들
Mat		image;										// 그림판 영상	

#include "menu.hpp"								// 아이콘 관련 헤더 파일
#include "icon_flag.hpp"							// 아이콘 상수

int main()
{
	image = Mat(500, 800, CV_8UC3, Scalar(255, 255, 255));
	place_icons(Size(60, 60));							// 아이콘 배치, 아이콘 크기

	Rect last_icon = *(icons.end() - 1);				// 아이콘 사각형 마지막 원소
	Point start_pale = Point(0, last_icon.br().y + 5);	// 팔레트 시작위치

	icons.push_back(Rect(start_pale, Size(100, 100)));	// 팔레트 사각형 추가
	icons.push_back(Rect(start_pale + Point(105, 0), Size(15, 100))); // 색상인덱스 사각형

	create_hueIndex(icons[HUE_IDX]);					// 팔레트 생성	
	create_palette(start_pale.y, icons[PALETTE]);		// 색상인덱스 생성

	imshow("image", image);
	waitKey();
	return 0;
}