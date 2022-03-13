#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#define		DRAW_RECTANGLE		0
#define		DRAW_CIRCLE			1
#define		DRAW_ECLIPSE		2
#define		DRAW_LINE			3
#define		DRAW_BRUSH			4
#define		ERASE		 		5
#define		OPEN		 	6
#define		SAVE		 	7
#define		PLUS	 		8
#define		MINUS	 		9
#define		CREAR			10

#define		COLOR	 		11
#define		PALETTE	 		12
#define		PALE_IDX	 	13

int  hue, thickness = 3;
int mouse_mode = 0, draw_mode = 0;

vector<Rect> btn;
Mat		image, canvas;
Point   palette_pt, pt1, pt2;
Scalar  Color(0, 0, 0);

#include "menu.hpp"


void  draw(Mat  image, Scalar color = Scalar(200, 200, 200))
{
	if (draw_mode == DRAW_RECTANGLE)
	{
		rectangle(image, pt1, pt2, color, thickness);
	}
	else if (draw_mode == DRAW_LINE)
	{
		line(image, pt1, pt2, color, thickness);
	}
	else if (draw_mode == DRAW_BRUSH)
	{
		line(image, pt1, pt2, color, thickness * 3);
		pt1 = pt2;
	}
	else if (draw_mode == ERASE)
	{
		line(image, pt1, pt2, Scalar(255, 255, 255), thickness * 5);
		pt1 = pt2;
	}
	else if (draw_mode == DRAW_CIRCLE)
	{
		Point2d pt3 = pt1 - pt2;
		int  radius = (int)sqrt(pt3.x*pt3.x + pt3.y*pt3.y);	// 두 좌표간 거리
		circle(image, pt1, radius, color, thickness);
	}
	else if (draw_mode == DRAW_ECLIPSE)
	{
		Point2d center = (pt1 + pt2) / 2.0;
		Size2d  size = pt1 - pt2;
		size.width = abs(size.width) / 2.0;
		size.height = abs(size.height) / 2.0;

		ellipse(image, center, size, 0, 0, 360, color, thickness);
	}
	imshow("그림판", image);
}

void  command(int command_mode)
{
	if (command_mode == PALETTE)
	{
		float  ratio1 = 256.0f / btn[PALETTE].height;
		float  ratio2 = 256.0f / btn[PALETTE].width;

		Point pt = pt2 - palette_pt;
		int saturation = cvRound(pt.x * ratio2);
		int intensity  = cvRound((btn[PALETTE].height - pt.y - 1) *ratio1);
		Scalar  hsi(hue, saturation, intensity );

		Mat    m_color = image(btn[COLOR]);
		m_color.setTo(hsi);
		cvtColor(m_color, m_color, CV_HSV2BGR);
		rectangle(image, btn[COLOR], Scalar(0, 0, 0), 1);

		Color = Scalar(m_color.at < Vec3b >(10, 10));
	}
	else if (command_mode == PALE_IDX)
	{
		make_palette(pt2.y, btn[PALETTE]);
	}

	else  if (command_mode == CREAR)
	{
		canvas.setTo(Scalar(255, 255, 255));
		mouse_mode = 0;
	}
	else  if (command_mode == OPEN)
	{
		Mat tmp = imread("../image/my_picture.jpg", 1);
		CV_Assert(!tmp.empty());

		resize(tmp, tmp, canvas.size());
		tmp.copyTo(canvas);
	}
	else  if (command_mode == SAVE)
	{
		imwrite("../image/my_save.jpg", canvas);
	}
	else  if (command_mode == PLUS)
	{
		canvas += Scalar(10, 10, 10);
	}
	else  if (command_mode == MINUS)
	{
		canvas -= Scalar(10, 10, 10);
	}

	imshow("그림판", image);
}


static void onMouse(int event, int x, int y, int, void*)
{
	Point pt(x, y);
	if (event == EVENT_LBUTTONUP)
	{
		for (int i = 0; i < (int)btn.size(); i++) {
			if (btn[i].contains(pt)) 	{
				if (i < 6)  {
					mouse_mode = 0;
					draw_mode = i;
				}
				else {		command(i);			}
				return;
			}
		}
		pt2 = pt;
		mouse_mode = 1;
		draw(image, Color);
	}
	else if (event == EVENT_LBUTTONDOWN)
	{
		pt1 = pt;
		mouse_mode = 2;
	}

	if (mouse_mode >= 2){
		Rect rect(0, 0, 125, image.rows);
		mouse_mode = (rect.contains(pt)) ? 0 : 3;
		pt2 = pt;
	}
}

void  onThickbar(int value, void*) {
	mouse_mode = 0;
}

int main()
{
	image = Mat(500, 800, CV_8UC3, Scalar(255, 255, 255));	// 그림판 영상
	
	Size   b_size(60, 60);
	replace_icon(b_size);

	Rect btn_last = *(btn.end() - 1);
	palette_pt = Point(0, btn_last.br().y + 5);

	Rect palette_rect(palette_pt, Size(100, 100));
	Rect pale_idx_rect(palette_pt + Point(105, 0), Size(15, 100));
	btn.push_back(palette_rect);
	btn.push_back(pale_idx_rect);

	make_palette(palette_pt.y, btn[PALETTE]);
	pallette_index(btn[PALE_IDX]);

	imshow("그림판", image);
	setMouseCallback("그림판", onMouse);

	createTrackbar("선굵기 ", "그림판", &thickness, 20, onThickbar);

	int  x = btn[1].br().x;
	canvas = image(Rect(x, 0, image.cols - x, image.rows));

	while (1)
	{
		if (mouse_mode == 1) 			// 마우스 버튼 떼기
			draw(image, Color);
		else if (mouse_mode == 3)		// 마우스 드래그
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