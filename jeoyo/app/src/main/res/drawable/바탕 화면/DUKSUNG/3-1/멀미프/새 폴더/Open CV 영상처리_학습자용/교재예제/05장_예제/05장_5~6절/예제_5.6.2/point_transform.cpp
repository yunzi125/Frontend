#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	vector<Point> rect_pt1, rect_pt2;	
	rect_pt1.push_back(Point(200, 50));
	rect_pt1.push_back(Point(400, 50));
	rect_pt1.push_back(Point(400, 250));
	rect_pt1.push_back(Point(200, 250));

	float theta = 20 * CV_PI / 180;
	Matx22f m( cos(theta), -sin(theta), sin(theta), cos(theta) );

	transform(rect_pt1, rect_pt2, m);

	Mat image(400, 500, CV_8UC3, Scalar(255, 255, 255));
	for (int i = 0; i < 4; i++)
	{
		line(image, rect_pt1[i], rect_pt1[(i + 1) % 4], Scalar(0, 0, 0), 1);
		line(image, rect_pt2[i], rect_pt2[(i + 1) % 4], Scalar(255, 0, 0), 2);
		cout << "rect_pt1[" + to_string(i) + "]=" << rect_pt1[i] << "\t";
		cout << "rect_pt2[" + to_string(i) + "]=" << rect_pt2[i] << endl;
	}
	imshow("image", image);
	waitKey();
	return 0;
}