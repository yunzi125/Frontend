#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

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

int main()
{
	Mat image = imread("../image/dct_test1.jpg", 0);
	CV_Assert(image.data);

	Mat  m_dct, m_idct;
	DCT_2D(image, m_dct, 8, 8, 0);
	DCT_2D(m_dct, m_idct, 8, 8, 1);

	m_idct.convertTo(m_idct, CV_8U);
	imshow("image", image);
	imshow("idct", m_idct);

	Rect rect(0, 0, 8, 8);
	cout << "첫 8x8 블록 원영상 화소" << endl;
	cout << image(rect) << endl << endl;
	cout << "첫 8x8 블록 DCT 결과" << endl;
	cout << m_dct(rect) << endl ;
	waitKey();
}