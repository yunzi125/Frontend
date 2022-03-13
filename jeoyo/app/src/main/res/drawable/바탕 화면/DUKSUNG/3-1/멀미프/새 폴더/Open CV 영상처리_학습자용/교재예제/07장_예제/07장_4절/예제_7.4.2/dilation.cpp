#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

bool check_match(Mat img, Point start, Mat mask, int mode )
{
	for (int u = 0; u < mask.rows; u++) {
		for (int v = 0; v < mask.cols; v++)	{
			int m = mask.at<uchar>(Point(v, u));				// 마스크 계수 	
			int p = img.at<uchar>(start + Point(v, u));		// 해당 위치 입력화소 

			bool ch = ( p == 255 ) ;				// 일치 여부 비교
			if (m == 1 && ch == mode )	return  false;
		}
	}
	return true;
}

void dilation(Mat img, Mat& dst, Mat mask)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	if (mask.empty())	mask = Mat(3, 3, CV_8UC1, Scalar(0));

	Point h_m = mask.size() / 2;
	for (int i = h_m.y; i < img.rows - h_m.y; i++){
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			Point start = Point(j, i) - h_m;
			bool  check = check_match(img, start, mask, 1);	// 원소 일치여부 비교
			dst.at<uchar>(i, j) = (check) ? 0 : 255;			// 침식연산과 반대
		}
	}
}

void morphology(Mat img, Mat& dst, Mat mask , int mode )
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	if (mask.empty())	mask = Mat(3, 3, CV_8UC1, Scalar(0));

	Point h_m = mask.size() / 2;

	for (int i = h_m.y; i < img.rows - h_m.y; i++){
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			Point start = Point(j, i) - h_m;
			bool  check = check_match(img, start, mask, mode);
			
			if		(mode == 0) dst.at<uchar>(i, j) = (check) ? 0 : 255;
			else if (mode == 1)	dst.at<uchar>(i, j) = (check) ? 255 : 0;
		}
	}
}

int main()
{
	Mat image = imread("../image/morph_test1.jpg", 0);
	CV_Assert(image.data);

	Mat th_img, dst1, dst2;
	threshold(image, th_img, 128, 255, CV_THRESH_BINARY);
	
	
	Matx < uchar, 3, 3> mask;
	mask << 0, 1, 0,
		1, 1, 1,
		0, 1, 1;

	dilation(th_img, dst1, (Mat)mask);
	morphologyEx(th_img, dst2, MORPH_DILATE, mask );

	imshow("image", image);	imshow("User_dilation", dst1);	
	imshow("OpenCV_dilation", dst2);
	waitKey();
	return 0;
}