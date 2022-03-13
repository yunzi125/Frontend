#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/perspective_test.jpg", IMREAD_COLOR);
	CV_Assert(image.data);

	Point2f pts1[4] = {
		Point2f(90, 170) , Point2f(300, 120),
		Point2f(90, 285), Point2f(300, 320)
	};
	Point2f pts2[4] = {
		Point2f(60, 120), Point2f(340, 110),
		Point2f(60, 280), Point2f(340, 280)
	};

	Mat dst(image.size(), CV_8UC1);
	Mat perspect_map = getPerspectiveTransform(pts1, pts2);
	warpPerspective(image, dst, perspect_map, image.size(), INTER_CUBIC);



	vector<Point3f> pts3, pts4;
	for (int i = 0; i < 4; i++) {
		pts3.push_back(Point3f(pts1[i].x, pts1[i].y, 1));
	}
	transform(pts3, pts4, perspect_map);
	cout << "[perspect_map] = " << endl << perspect_map << endl << endl;

	for (int i = 0; i < 4; i++)   
	{
		pts4[i] /= pts4[i].z;
		cout << "pts2[" << i << "]=" << pts2[i] << "\t";
		cout << "pts4[" << i << "]=" << pts4[i] << endl;

		circle(image, pts1[i], 2, Scalar(0,0, 255), 2);
		circle(dst, pts2[i], 2 , Scalar(0, 0, 255), 2);
	}

	imshow("image ", image);
	imshow("dst - ¿Ö°î º¸Á¤", dst);
	waitKey();
	return 0;
}