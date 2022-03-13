#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// 평균값 필터링 
void averageFilter(Mat img, Mat& dst, int size)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++)
		{
			Point pt1 = Point(j - size / 2, i - size / 2);
			Point pt2 = pt1 + (Point)Size(size, size);

			if (pt1.x < 0) pt1.x = 0;
			if (pt1.y < 0) pt1.y = 0;
			if (pt2.x > img.cols)  pt2.x = img.cols;
			if (pt2.y > img.rows) pt2.y = img.rows;

			Rect  mask_rect(pt1, pt2);
			Mat  mask = img(mask_rect);
			dst.at<uchar>(i, j) = (uchar)mean(mask)[0];
		}
	}
}

int main()
{
	Mat image = imread("../image/avg_filter.jpg", IMREAD_GRAYSCALE );
	CV_Assert(image.data);

	Mat avg_img, blur_img, box_img;
	averageFilter(image, avg_img, 5);
	blur(image, blur_img, Size(5, 5));
	boxFilter(image, box_img, -1, Size(5, 5));

	imshow("image", image);
	imshow("avg_Filter_img", avg_img);
	imshow("blur_img", box_img);
	imshow("box_img", box_img);
	waitKey();
	return 0;
}