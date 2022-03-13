#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void calc_histo(const Mat& image, Mat& hist, Vec3i bins, Vec3f range)
{
	float   range1[] = { 0, range[0] };		// 각 채널 화소값 범위
	float   range2[] = { 0, range[1] };		// 각 채널 화소값 범위
	float   range3[] = { 0, range[2] };		// 각 채널 화소값 범위

	int		histSize[] = { bins[0], bins[1], bins[2] }; 	// 각 채널 계급개수
	int		channels[] = { 0, 1, 2 };			// 채널 목록
	int		dims = image.channels();			// 결과 행렬 차원수
	const float* ranges[] = { range1, range2, range3 };	// 모든 채널 화소범위

	calcHist(&image, 1, channels, Mat(), hist, dims, histSize, ranges);
}

void draw_histo(Mat hist, Mat &hist_img, Size size = Size(256, 200))
{
	hist_img = Mat(size, CV_8U, Scalar(255));
	float  bin = (float)hist_img.cols / hist.rows;
	normalize(hist, hist, 0, size.height, NORM_MINMAX);

	for (int i = 0; i<hist.rows; i++)
	{
		float idx1 = i * bin;
		float idx2 = (i + 1) * bin;
		Point2f pt1 = Point2f(idx1, 0);
		Point2f pt2 = Point2f(idx2, hist.at <float>(i));

		if (pt2.y > 0)
			rectangle(hist_img, pt1, pt2, Scalar(0), -1);
	}
	flip(hist_img, hist_img, 0);
}


// 히스토그램 계산과 그래프 그리기 통합
Mat create_hist(Mat img, Mat &hist)
{
	Mat  hist_img;
	Vec3f histsize(256, 0, 0), ranges(256, 0, 0);
	calc_histo(img, hist, histsize, ranges);
	draw_histo(hist, hist_img);

	return hist_img;
}

int main()
{
	Mat image = imread("../image/equalize_test.jpg", 0);
	CV_Assert(!image.empty());

	Mat hist, dst1, dst2;
	Mat hist_img1 = create_hist(image, hist);

	Mat accum_hist = Mat(hist.size(), hist.type(), Scalar(0));

	accum_hist.at<float>(0) = hist.at<float>(0);
	for (int i = 1; i < accum_hist.rows; i++){
		accum_hist.at<float>(i) = accum_hist.at<float>(i - 1) + hist.at<float>(i);
	}

	//accum_hist /= sum(hist)[0];
	//accum_hist *= 255; 
	//dst1 = Mat(image.size(), CV_8U);
	//for (int i = 0; i < image.rows; i++){
	//	for (int j = 0; j < image.cols; j++){
	//		int idx = image.at<uchar>(i, j);
	//		dst1.at<uchar>(i, j) = accum_hist.at<float>(idx);
	//	}
	//}

	normalize(accum_hist, accum_hist, 0, 255, NORM_MINMAX);
	accum_hist.convertTo(accum_hist, CV_8U);
	LUT(image, accum_hist, dst1);

	equalizeHist(image, dst2);

	Mat hist_img2 = create_hist(dst1, hist);
	Mat hist_img3 = create_hist(dst2, hist);

	imshow("image", image);
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("hist_img1", hist_img1);
	imshow("hist_img2", hist_img2);
	imshow("hist_img3", hist_img3);

	waitKey();
	return 0;
}