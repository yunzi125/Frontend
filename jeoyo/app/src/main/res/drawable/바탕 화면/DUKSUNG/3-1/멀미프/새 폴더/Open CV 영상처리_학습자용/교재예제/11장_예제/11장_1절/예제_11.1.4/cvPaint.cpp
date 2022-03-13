#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

vector<Rect> icons;
Mat	 image, canvas;;
int  mouse_mode = 0, draw_mode = 0;
Point	pt1, pt2;
Scalar  Color(0, 0, 0);
int		thickness = 3;

#include "menu.hpp"
#include "icon_flag.hpp"
#include "draw.hpp"
#include "event.hpp"

void  onTrackbar(int value, void*) {
	mouse_mode = 0;
}

int main()
{
	image = Mat(500, 800, CV_8UC3, Scalar(255, 255, 255));	// 그림판 영상
	place_icons(Size(60, 60));						// 아이콘 배치, 아이콘 크기

	Rect last_icon = *(icons.end() - 1);				// 아이콘 사각형 마지막 원소
	Point start_pale = Point(0, last_icon.br().y + 5);		// 마지막 아이콘 5픽셀 아래

	icons.push_back(Rect(start_pale, Size(100, 100)));	// 팔레트 사각형 추가
	icons.push_back(Rect(start_pale + Point(105, 0), Size(15, 100))); // 색상인덱스 사각형 추가

	create_hueIndex(icons[HUE_IDX]);					// 팔레트 생성	
	create_palette(start_pale.y, icons[PALETTE]);		// 색상인덱스 생성

	imshow("그림판", image);
	setMouseCallback("그림판", onMouse);

	createTrackbar("선굵기 ", "그림판", &thickness, 20, onTrackbar);	// 트렉바 등록
	int  x = icons[1].br().x;									// 두번째 아이콘 x좌표 
	Rect canvas_rect(x, 0, image.cols - x, image.rows);			// 그림(캔버스) 영역 
	canvas = image(canvas_rect);									// 캔버스 행렬 

	while (1)
	{
		if (mouse_mode == 1) 			// 마우스 버튼 떼기
			draw(image, Color);
		else if (mouse_mode == 3)			// 마우스 드래그
		{
			if (draw_mode == DRAW_BRUSH || draw_mode == ERASE) {
				draw(image, Color);
			}
			else {
				draw(image.clone());
			}
		}
		if (waitKey(30) == 27)  break;
	}

	waitKey();
	return 0;
}