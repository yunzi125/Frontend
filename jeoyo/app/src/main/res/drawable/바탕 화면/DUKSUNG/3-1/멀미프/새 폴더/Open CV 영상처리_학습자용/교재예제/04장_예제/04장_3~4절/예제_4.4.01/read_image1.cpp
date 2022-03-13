#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void  print_matInfo(string name, Mat img)
{
	string str;
	int depth = img.depth();

	if (depth == CV_8U)	 str = "CV_8U";
	else if (depth == CV_8S)	 str = "CV_8S";
	else if (depth == CV_16U) str = "CV_16U";
	else if (depth == CV_16S)	 str = "CV_16S";
	else if (depth == CV_32S) str = "CV_32S";
	else if (depth == CV_32F) str = "CV_32F";
	else if (depth == CV_64F) str = "CV_64F";

	cout << name;
	cout << format(": depth(%d) channels(%d) -> 자료형: ", depth, img.channels());
	cout << str << "C" << img.channels() << endl;
}

int main()
{
	string filename1 = "../image/read_gray.jpg";
	Mat gray2gray = imread(filename1, IMREAD_GRAYSCALE);
	Mat gray2color = imread(filename1, IMREAD_COLOR);
	CV_Assert(gray2gray.data && gray2color.data );

	Rect roi(100, 100, 1, 1);
	cout << "행렬 좌표 (100,100) 화소값 " << endl;
	cout << "gray2gray " << gray2gray(roi) << endl;
	cout << "gray2color " << gray2color(roi) << endl << endl;

	print_matInfo("gray2gray", gray2gray);
	print_matInfo("gray2color", gray2color);
	imshow("gray2gray", gray2gray);
	imshow("gray2color", gray2color);
	waitKey(0);
	return 0;
}