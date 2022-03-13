#include <opencv2/opencv.hpp>
#include <time.h>
using namespace cv;
using namespace std;

Mat calc_cosine(int N, int M)
{
	Mat DCTCoeff(N, M, CV_64F);
	double alpha = sqrt(2.0 / N);
	double denominator = 2.0 * N;

	for (int j = 0; j < N ; j++) {
		DCTCoeff.at<double>(0, j) = sqrt(1.0 / N);
	}

	for (int j = 0; j < N; j++) {
		for (int i = 1; i < M; i++) {
			double radian = ((2 * j + 1) * i * CV_PI) / denominator;
			DCTCoeff.at<double>(i, j) = alpha * cos(radian);
		}
	}
	return DCTCoeff;
}


void DCT_2D_fast(Mat img, Mat& dst, int N, int M, int dir)
{
	dst = Mat(img.size(), CV_64F, Scalar(0) );
	img.convertTo(img, CV_64F);
	Mat cos_mat = calc_cosine(N, M);
	Mat cos_mat_t = cos_mat.t();

	for (int bi = 0; bi < img.rows; bi += N) {
		for (int bj = 0; bj < img.cols; bj += M)
		{
			Rect rect(Point(bj, bi), Size(M, N));
			Mat block;
			
			multiply(img(rect), cos_mat, block);
			multiply(block, cos_mat_t, block);
			block.copyTo(dst(rect));
		}
	}
}

int main()
{
	Mat image = imread("../image/dct_test1.jpg", 0);
	CV_Assert(image.data);

	Mat  m_dct, m_idct;

	DCT_2D_fast(image, m_dct, 8, 8, 1);

	Rect rect(0, 0, 8, 8);
	cout << "첫 8x8 블록 원영상 화소" << endl;
	cout << image(rect) << endl << endl;
	cout << "첫 8x8 블록 DCT 결과" << endl;
	cout << m_dct(rect) << endl;

	imshow("image", image);
//	imshow("m_idct", m_idct);
	waitKey();

	return 0;
}