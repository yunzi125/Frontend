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
	string filename = "../image/read_color.jpg";
	Mat color2gray = imread(filename, IMREAD_GRAYSCALE);
	Mat color2color = imread(filename, IMREAD_COLOR);
	CV_Assert(color2gray.data && color2color.data);

	Rect roi(100, 100, 1, 1);
	cout << "행렬 좌표 (100,100) 화소값 " << endl;
	cout << "color2gray " << color2gray(roi) << endl;
	cout << "color2color " << color2color(roi) << endl ;

	print_matInfo("color2gray", color2gray);
	print_matInfo("color2color", color2color);
	imshow("color2gray", color2gray);
	imshow("color2color", color2color);
	waitKey(0);
	return 0;
}