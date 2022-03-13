#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void translation(Mat img, Mat& dst, Point pt)				// 평행이동 함수
{
	Rect rect(Point(0, 0), img.size());						// 입력영상 범위 사각형
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++) {				// 목적영상 순회 - 역방향 사상
		for (int j = 0; j < dst.cols; j++)
		{
			Point dst_pt(j, i);						// 목적영상 좌표
			Point img_pt = dst_pt - pt;			// 입력영상 좌표
			if (rect.contains(img_pt))				// 입력영상 범위 확인
				dst.at<uchar>(dst_pt) = img.at<uchar>(img_pt);
		}
	}
}

int main()
{
	Mat image = imread("../image/translation_test.jpg", 0);
	CV_Assert(image.data);
	
	Mat dst1, dst2;
	translation(image, dst1, Point(30, 80));		// 평행이동 수행
	translation(image, dst2, Point(-80, -50));

	imshow("image", image);
	imshow("dst1 - ( 30, 80) 이동", dst1);
	imshow("dst2 - (-80, -50) 이동", dst2);
	waitKey();
	return 0;
}