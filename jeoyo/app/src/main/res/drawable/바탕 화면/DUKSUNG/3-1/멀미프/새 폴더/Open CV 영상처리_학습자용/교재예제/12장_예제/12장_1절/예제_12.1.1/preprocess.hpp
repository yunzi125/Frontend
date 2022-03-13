#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void draw_rotatedRect(Mat &img, RotatedRect mr, Scalar color, int thickness = 2)
{
	Point2f  pts[4];
	mr.points(pts);

	for (int i = 0; i <4; ++i) {
		line(img, pts[i], pts[(i + 1) % 4], color, thickness);
	}
}

Mat  preprocessing(Mat img)				// 전처리
{
	Mat gray, th_img;
	cvtColor(img, gray, CV_BGR2GRAY);
	GaussianBlur(gray, gray, Size(7, 7), 2, 2);

	threshold(gray, th_img, 130, 255, THRESH_BINARY | THRESH_OTSU);
	morphologyEx(th_img, th_img, MORPH_OPEN, Mat(), Point(-1, -1), 1);
	return th_img;
}

// 검출 영역 원좌표로 반환 
vector<RotatedRect>  find_coins(Mat img)
{
	vector<vector<Point> > contours;
	findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	Mat col;
	cvtColor(img, col, CV_GRAY2BGR);

	vector<RotatedRect> circles;
	for (int i = 0; i< (int)contours.size(); i++)
	{
		RotatedRect  mr = minAreaRect(contours[i]);
		float radius = (mr.size.width + mr.size.height) / 4.0f;

		//		circle(col, mr.center,2 , Scalar(255, 0, 0), 2);
		//		draw_rotatedRect(col, mr, Scalar(0, 255, 0), 2);
		//		imshow("img", col);

		if (radius > 18) circles.push_back(mr);
	}
	return circles;
}