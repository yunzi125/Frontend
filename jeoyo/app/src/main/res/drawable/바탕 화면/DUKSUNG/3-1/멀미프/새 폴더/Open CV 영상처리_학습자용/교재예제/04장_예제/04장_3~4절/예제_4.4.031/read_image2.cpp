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

	//cout << name << " depth " << depth << endl;
	//cout << name << " channels " << img.channels() << endl;
	//cout << name << " 자료형 " << str << "C" << img.channels();

	cout << name;
	cout << format(": depth(%d) channels(%d) -> 자료형: ", depth, img.channels());
	cout << str << "C" << img.channels() << endl;
}

int main()
{
	string filename1 = "../image/read_16.tif";		// 16비트 영상
	string filename2 = "../image/read_32.tif";		// 32비트 영상

	Mat color2unchanged1 = imread(filename1, IMREAD_UNCHANGED);
	Mat color2unchanged2 = imread(filename2, IMREAD_UNCHANGED);
	CV_Assert(color2unchanged1.data && color2unchanged2.data);

	Rect roi(100, 100, 1, 1);
	cout << "16/32비트 영상 행렬 좌표 (100,100) 화소값 " << endl;
	cout << "color2unchanged1 " << color2unchanged1(roi) << endl;
	cout << "color2unchanged2  " << color2unchanged2(roi) << endl;

	print_matInfo("color2unchanged1", color2unchanged1);
	print_matInfo("color2unchanged2", color2unchanged2);

	imshow("color2unchanged1", color2unchanged1);
	imshow("color2unchanged2", color2unchanged2);
	waitKey(0);
	return 0;
}