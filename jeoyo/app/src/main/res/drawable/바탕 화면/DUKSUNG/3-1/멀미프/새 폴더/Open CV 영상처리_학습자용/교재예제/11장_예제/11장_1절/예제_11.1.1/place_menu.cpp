#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// �������� ����
vector<Rect> icons;								// ������ �簢����
Mat		image;										// �׸��� ����	

#include "menu.hpp"								// ������ ���� ��� ����
#include "icon_flag.hpp"							// ������ ���

int main()
{
	image = Mat(500, 800, CV_8UC3, Scalar(255, 255, 255));
	place_icons(Size(60, 60));							// ������ ��ġ, ������ ũ��

	Rect last_icon = *(icons.end() - 1);				// ������ �簢�� ������ ����
	Point start_pale = Point(0, last_icon.br().y + 5);	// �ȷ�Ʈ ������ġ

	icons.push_back(Rect(start_pale, Size(100, 100)));	// �ȷ�Ʈ �簢�� �߰�
	icons.push_back(Rect(start_pale + Point(105, 0), Size(15, 100))); // �����ε��� �簢��

	create_hueIndex(icons[HUE_IDX]);					// �ȷ�Ʈ ����	
	create_palette(start_pale.y, icons[PALETTE]);		// �����ε��� ����

	imshow("image", image);
	waitKey();
	return 0;
}