#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#define		COLOR	 		11
#define		PALETTE	 		12
#define		PALE_IDX	 	13

vector<Rect> btn;
Mat		image;

Point   palette_pt;
int  hue;

int mouse_mode = 0, command_mode = 0, draw_mode = 0;
Point	pt1, pt2;

void replace_icon(Size b_size)
{
	vector<string> btn_icon = {
		"rect", "circle", "eclipe", "line", "brush", "eraser",
		"open", "save", "clear", "plus", "minus", "color"
	};

	int btn_rows = (int)cvCeil(btn_icon.size() / 2.0);

	for (int i = 0, k = 0; i < btn_rows; i++) {
		for (int j = 0; j < 2; j++, k++)
		{
			Point   pt(j*b_size.width, i*b_size.height);
			btn.push_back(Rect(pt, b_size));

			Mat icon = imread("../image/icon/" + btn_icon[k] + ".jpg", 1);
			if (icon.empty()) continue;

			resize(icon, icon, b_size);
			icon.copyTo(image(btn[k]));
		}
	}
}


void  make_palette(int pos_y, Rect rect)
{
	Mat    palatte = image(rect);
	float  ratio1 = 180.0f / rect.height;		// hue 범위 스케일
	float  ratio2 = 256.0f / rect.width;			// saturation 범위 스케일 
	float  ratio3 = 256.0f / rect.height;		// intensity 범위 스케일

	hue = cvRound((pos_y - rect.y) * ratio1);

	for (int i = 0; i < palatte.rows; i++){
		for (int j = 0; j < palatte.cols; j++)
		{
			int saturation = cvRound(j*ratio2);
			int intensity = cvRound((palatte.rows - i - 1)*ratio3);

			palatte.at<Vec3b>(i, j) = Vec3b(hue, saturation, intensity);
		}
	}
	cvtColor(palatte, palatte, CV_HSV2BGR);
}

void  pallette_index(Rect rect)
{
	Mat  p_index = image(rect);
	float  ratio = 180.0f / rect.height;

	for (int i = 0; i < p_index.rows; i++)
	{
		Scalar  hue_color(i*ratio, 255, 255);
		p_index.row(i).setTo(hue_color);
	}
	cvtColor(p_index, p_index, CV_HSV2BGR);
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
				else
					command_mode = i;
				return;
			}
		}
		pt2 = pt;
		mouse_mode = 1;
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

int main()
{
	image = Mat(500, 800, CV_8UC3, Scalar(255, 255, 255));	// 그림판 영상
	Scalar  Color(0, 0, 0);
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

	setMouseCallback("그림판", onMouse);
	imshow("image", image);
	waitKey();
	return 0;
}