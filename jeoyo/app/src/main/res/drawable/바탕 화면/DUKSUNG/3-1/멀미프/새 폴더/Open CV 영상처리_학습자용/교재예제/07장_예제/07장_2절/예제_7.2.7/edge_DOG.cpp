#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat getLoGmask(Size size, double sigma)
{
	double ratio = 1 / (CV_PI * pow(sigma, 4.0));
	int center = size.height / 2;
	Mat dst(size, CV_64F);

	for (int i = 0; i < size.height; i++){
		for (int j = 0; j < size.width; j++)
		{
			int x2 = (j - center) * (j - center);
			int y2 = (i - center) * (i - center);

			double value = (x2 + y2) / (2 * sigma * sigma);
			dst.at<double>(i, j) = -ratio * (1 - value) * exp(-value);
		}
	}

	double scale = (center * 10 / ratio);
	return dst * scale;
}

int main()
{
	Mat image = imread("../image/laplacian_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	double sigma = 1.4;
	Mat LoG_mask = getLoGmask(Size(9, 9), sigma);

	cout << LoG_mask << endl;
	cout << sum(LoG_mask) << endl;

	Mat dst1, dst2, dst3, dst4, gaus_img;
	filter2D(image, dst1, -1, LoG_mask);
	GaussianBlur(image, gaus_img, Size(9, 9), sigma, sigma);
	Laplacian(gaus_img, dst2, -1, 5);

	GaussianBlur(image, dst3, Size(1, 1), 0.0);
	GaussianBlur(image, dst4, Size(9, 9), 1.6);
	Mat dst_DoG = dst3 - dst4;

	normalize(dst_DoG, dst_DoG, 0, 255, CV_MINMAX);

	imshow("image", image);
	imshow("dst1 - LoG_filter2D", dst1);
	imshow("dst2 - LOG_OpenCV", dst2);
	imshow("dst_DoG - DOG_OpenCV", dst_DoG);
	waitKey();
	return 0;
}