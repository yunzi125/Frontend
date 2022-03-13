#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat img8 = imread("../image/read_color.jpg", IMREAD_COLOR);
	CV_Assert(img8.data);

	vector<int> params_jpg, params_png;
	params_jpg.push_back(IMWRITE_JPEG_QUALITY);
	params_jpg.push_back(50);

	params_png.push_back(IMWRITE_PNG_COMPRESSION);
	params_png.push_back(9);

	imwrite("../image/write_test1.jpg", img8);
	imwrite("../image/write_test2.jpg", img8, params_jpg);
	imwrite("../image/write_test.png", img8, params_png);
	imwrite("../image/write_test.bmp", img8);

	Mat img16, img32;
	img8.convertTo(img16, CV_16U, 65535 / 255.0);
	img8.convertTo(img32, CV_32F, 1 / 255.0f);

	Rect  roi(10, 10, 3, 3);
	cout << "img8 青纺狼 老何 " << endl << img8(roi) << endl << endl;
	cout << "img16 青纺狼 老何 " << endl << img16(roi) << endl << endl;
	cout << "img32 青纺狼 老何 " << endl << img32(roi) << endl << endl;

	imwrite("../image/write_test_16.tif", img16);
	imwrite("../image/write_test_32.tif", img32);

	imshow("img16", img16);
	imshow("img32", img32);
	waitKey();
	return 0;
}