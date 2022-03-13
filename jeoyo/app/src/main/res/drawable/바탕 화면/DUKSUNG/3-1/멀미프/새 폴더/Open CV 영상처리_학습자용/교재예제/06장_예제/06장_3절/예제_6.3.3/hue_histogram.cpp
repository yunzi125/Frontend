#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void  calc_Histo(const Mat& image, Mat& hist, int bins, int range_max = 256)
{
	int		histSize[] = { bins };			// ������׷� ��� ����
	float   range[] = { 0, (float)range_max };		// ������׷� ����
	int		channels[] = { 0 };				// ä�� ���
	int		dims = image.channels();;
	const float* ranges[] = { range };

	calcHist(&image, 1, channels, Mat(), hist, dims, histSize, ranges);
}

// hue ä�ο� ���� ���� �ȷ�Ʈ ��� ����
Mat  make_palatte(int rows)
{
	Mat hsv(rows, 1, CV_8UC3);
	for (int i = 0; i < rows; i++)
	{
		uchar hue = saturate_cast<uchar>((float)i / rows * 180);
		hsv.at<Vec3b>(i) = Vec3b(hue, 255, 255);
	}
	cvtColor(hsv, hsv, CV_HSV2BGR);
	return hsv;
}

void draw_hist_hue(Mat hist, Mat &hist_img, Size size = Size(256, 200))
{
	Mat hsv_palatte = make_palatte(hist.rows);

	hist_img = Mat(size, CV_8UC3, Scalar(255, 255, 255));
	float  bin = (float)hist_img.cols / hist.rows;
	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

	for (int i = 0; i<hist.rows; i++)
	{
		float start_x = (i * bin);
		float  end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at <float>(i));

		Scalar color = hsv_palatte.at<Vec3b>(i);
		rectangle(hist_img, pt1, pt2, color, -1);
	}
	flip(hist_img, hist_img, 0);
}

int main()
{
	Mat image = imread("../image/pixel_test.jpg", CV_LOAD_IMAGE_COLOR);
	CV_Assert(!image.empty());

	Mat HSV_img, HSV_arr[3];
	cvtColor(image, HSV_img, CV_BGR2HSV);
	split(HSV_img, HSV_arr);

	Mat hist_hue, hist_hue_img;
	calc_Histo(HSV_arr[0], hist_hue, 18, 180);
	draw_hist_hue(hist_hue, hist_hue_img, Size(360, 200));

	imshow("hist_hue_img", hist_hue_img);
	imshow("image", image);
	waitKey();
	return 0;
}