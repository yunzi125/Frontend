#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

vector<Rect> icons; 
Mat		image;
int		mouse_mode = 0, draw_mode = 0;
Point	pt1, pt2;
Scalar Color(0,0,0);

#include "menu.hpp"
#include "icon_flag.hpp"

int		thickness = 3;

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
		int  radius = (int)sqrt(pt3.x*pt3.x + pt3.y*pt3.y);	// �� ��ǥ�� �Ÿ�
		circle(image, pt1, radius, color, thickness);
	}
	else if (draw_mode == DRAW_ECLIPSE)
	{
		Point2d center = (pt1 + pt2) / 2.0;
		Size2d  size = (pt1 - pt2) / 2.0 ;
		size.width  = abs(size.width) ,
		size.height = abs(size.height);
		ellipse(image, center, size, 0, 0, 360, color, thickness);
	}
	imshow("�׸���", image);
}

void  command(int mode)				// �Ϲ� ��� ����
{
	if (mode == PALETTE)						// �ȷ�Ʈ ���� Ŭ��
	{
		float  ratio1 = 256.0f / icons[PALETTE].width;		// �ʺ�� ä�� ���� ����
		float  ratio2 = 256.0f / icons[PALETTE].height;		// ���̷� �� ���� ����

		Point pt = pt2 - icons[PALETTE].tl();						// �ȷ�Ʈ �� Ŭ����ǥ
		int saturation = cvRound(pt.x * ratio1);
		int value = cvRound((icons[PALETTE].height - pt.y - 1) *ratio2);
		Scalar  hsv(hue, saturation, value);					// HSV ���� ����

		Mat    m_color = image(icons[COLOR]);			// ��������� ����
		m_color.setTo(hsv);
		cvtColor(m_color, m_color, CV_HSV2BGR);		// HSV �� BGR ��ȯ
		rectangle(image, icons[COLOR], Scalar(0, 0, 0), 1);	// ���� ������ �׵θ���

		Color = Scalar(m_color.at < Vec3b >(10, 10));
	}
	else if (mode == HUE_IDX)							// �����ε��� Ŭ����
	{
		create_palette(pt2.y, icons[PALETTE]);				// �ȷ�Ʈ �ٽ� �׸���
	}

	imshow("�׸���", image);
}

static void onMouse(int event, int x, int y, int, void*)
{
	Point pt(x, y);
	if (event == EVENT_LBUTTONUP) 				// ���ʹ�ư ����
	{
		for (int i = 0; i < (int)icons.size(); i++) 		// �޴������� �簢�� ��ȸ
		{
			if (icons[i].contains(pt)) {					// �޴� Ŭ�� ���� �˻�
				if (i < 6)  							// �׸��� ����̸�
				{
					mouse_mode = 0;					// ���콺 ���� �ʱ�ȭ
					draw_mode = i;					// �׸��� ���
				}
				else		command(i);					// �Ϲ� ����̸�
				return;
			}
		}
		pt2 = pt;										// ������ǥ ����
		mouse_mode = 1;								// ��ư ���� ���� ����
	}
	else if (event == EVENT_LBUTTONDOWN) 	// ���ʹ�ư ������
	{
		pt1 = pt;										// ������ǥ ����
		mouse_mode = 2;
	}

	if (mouse_mode >= 2) {							// ���ʹ�ư ������ or �巡�� 
		Rect rect(0, 0, 125, image.rows);
		mouse_mode = (rect.contains(pt)) ? 0 : 3;		// ���콺 ���� ����
		pt2 = pt;
	}
}

int main()
{
	image = Mat(500, 800, CV_8UC3, Scalar(255, 255, 255));	// �׸��� ����
	place_icons(Size(60, 60));						// ������ ��ġ, ������ ũ��

	Rect last_icon = *(icons.end() - 1);				// ������ �簢�� ������ ����
	Point start_pale = Point(0, last_icon.br().y + 5);		// ������ ������ 5�ȼ� �Ʒ�
	icons.push_back(Rect(start_pale, Size(100, 100)));	// �ȷ�Ʈ �簢�� �߰�
	icons.push_back(Rect(start_pale + Point(105, 0), Size(15, 100))); // �����ε��� �簢�� �߰�

	create_hueIndex(icons[HUE_IDX]);					// �ȷ�Ʈ ����	
	create_palette(start_pale.y, icons[PALETTE]);		// �����ε��� ����

	imshow("�׸���", image);
	setMouseCallback("�׸���", onMouse);

	while (1)
	{
		if (mouse_mode == 1) 				// ���콺 ��ư ����
			draw(image, Color);
		else if (mouse_mode == 3)			// ���콺 �巡��
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
	return 0;
}