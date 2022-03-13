#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void minMaxFilter(Mat img, Mat& dst, int size, int flag = 1)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	Size msize(size, size);
	Point h_m = msize / 2;

	for (int i = h_m.y; i < img.rows - h_m.y; i++) {			// 입력 영상 조회
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			Point start = Point(j, i) - h_m;
			Rect roi(start, msize);						// 마스크 영역 사각형
			Mat  mask = img(roi);						// 마스크 영역 참조

			double minVal, maxVal;
			minMaxLoc(mask, &minVal, &maxVal);	// 마스크 영역 최소, 최대값
			dst.at<uchar>(i, j) = (flag) ? maxVal : minVal;
		}
	}
}

int main()
{
	Mat image = imread("../image/min_max.jpg", 0);
	CV_Assert(image.data);

	Mat min_img, max_img;
	minMaxFilter(image, min_img, 5, 0);		// 5x5 마스크 최소값 필터링
	minMaxFilter(image, max_img, 5, 1);		// 5x5 마스크 최대값 필터링

	imshow("image", image);
	imshow("minFilter_img", min_img);
	imshow("maxFilter_img", max_img);
	waitKey();
	return 0;
}