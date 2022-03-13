#include <opencv2/opencv.hpp>
#include <time.h>
using namespace cv;
using namespace std;

Mat calc_cosine(int N, int M)
{
	Mat cos_mat(N*N, M*M, CV_32F);

	for (int k = 0; k < N; k++) {
		for (int l = 0; l < M; l++)
		{
			Point idx(l*M, k*N);
			for (int n = 0; n < N; n++) {
				for (int m = 0; m < M; m++)
				{
					float theta1 = (float)((2 * n + 1) * k * CV_PI / (2 * N));
					float theta2 = (float)((2 * m + 1) * l * CV_PI / (2 * M));

					cos_mat.at<float>(idx + Point(m, n)) = cos(theta1) * cos(theta2);
				}
			}
		}
	}
	return cos_mat;
}

Mat DCT_block(Mat g)
{
	Mat dst(g.size(), g.type());
	int N = g.rows, M = g.cols;

	for (int k = 0; k < N; k++) {
		for (int l = 0; l < M; l++){
			float sum = 0;
			for (int n = 0; n < N; n++) {
				for (int m = 0; m < M; m++)
				{
					float theta1 = (float)((2 * n + 1) * k * CV_PI / (2 * N));
					float theta2 = (float)((2 * m + 1) * l * CV_PI / (2 * M));
					sum += g.at<float>(n, m) * cos(theta1) * cos(theta2);
				}
			}
			float ck = (k) ? sqrt(2.0f / N) : sqrt(1.0f / N);
			float cl = (l) ? sqrt(2.0f / M) : sqrt(1.0f / M);
			dst.at<float>(k, l) = ck * cl * sum;
		}
	}
	return dst;
}

Mat IDCT_block(Mat f)
{
	Mat dst(f.size(), f.type());
	int N = f.rows, M = f.cols;

	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			float sum = 0;
			for (int k = 0; k < N; k++)	{
				for (int l = 0; l < M; l++)
				{
					float theta1 = (float)((2 * n + 1) * k * CV_PI / (2 * N));
					float theta2 = (float)((2 * m + 1) * l * CV_PI / (2 * M));

					float ck = (k) ? sqrt(2.0f / N) : sqrt(1.0f / N);
					float cl = (l) ? sqrt(2.0f / M) : sqrt(1.0f / M);
					sum += ck * cl * f.at<float>(k, l) * cos(theta1) * cos(theta2);
				}
			}
			dst.at<float>(n, m) = sum;
		}
	}
	return dst;
}

void DCT_2D(Mat img, Mat& dst, int N, int M, int dir)
{
	dst = Mat(img.size(), CV_32F);
	img.convertTo(img, CV_32F);
	for (int bi = 0; bi < img.rows; bi += N) {
		for (int bj = 0; bj < img.cols; bj += M)
		{
			Rect rect(Point(bj, bi), Size(M, N));
			Mat block = img(rect);
			Mat new_block = (dir==0) ? DCT_block(block) : IDCT_block(block);
			new_block.copyTo(dst(rect));
		}
	}
}

Mat DCT_block(Mat g, Mat cos_mat, int dir)
{
	Mat dst(g.size(), g.type(), Scalar(0));
	int N = g.rows, M = g.cols;
	Vec2f CK(sqrt(1.0f / N), sqrt(2.0f / N));
	Vec2f CL(sqrt(1.0f / M), sqrt(2.0f / M));

	for (int k = 0; k < N; k++) {
		for (int l = 0; l < M; l++)
		{
			float ck = (k) ? CK[1] : CK[0];
			float cl = (l) ? CL[1] : CL[0];
			Point idx(l*M, k*N);
			for (int n = 0; n < N; n++) {
				for (int m = 0; m < M; m++)
				{
					float cos_value = cos_mat.at<float>(idx + Point(m, n));
					float coef = (dir==0) ? g.at<float>(n, m) : g.at<float>(k, l);

					if (dir==0) dst.at<float>(k, l) += ck * cl * coef * cos_value;
					else		dst.at<float>(n, m) += ck * cl * coef * cos_value;
				}
			}
		}
	}
	return dst;
}

void DCT_2D_fast(Mat img, Mat& dst, int N, int M, int dir)
{
	dst = Mat(img.size(), CV_32F);
	img.convertTo(img, CV_32F);
	Mat cos_mat = calc_cosine(N, M);

	for (int bi = 0; bi < img.rows; bi += N) {
		for (int bj = 0; bj < img.cols; bj += M)
		{
			Rect rect(Point(bj, bi), Size(M, N));
			Mat block = img(rect);
			Mat new_block = DCT_block(block, cos_mat, dir);
			new_block.copyTo(dst(rect));
		}
	}
}

int main()
{
	Mat image = imread("../image/dct_test1.jpg", 0);
	CV_Assert(image.data);

	Mat  m_dct, m_idct;

	clock_t start = clock();
	DCT_2D(image, m_dct, 8, 8, 0);
	DCT_2D(m_dct, m_idct, 8, 8, 1);
	printf("normal DCT + IDCT 시간 %5.1f ms\n", (double)(clock() - start));

	m_idct.convertTo(m_idct, CV_8U);
	imshow("m_idct1", m_idct);

	start = clock();
	DCT_2D_fast(image, m_dct, 8, 8, 0);
	DCT_2D_fast(m_dct, m_idct, 8, 8, 1);
	printf(" fast  DCT + IDCT 시간 %5.1f ms\n", (double)(clock() - start));

	m_idct.convertTo(m_idct, CV_8U);
	imshow("m_idct2", m_idct);
	waitKey();

	return 0;
}