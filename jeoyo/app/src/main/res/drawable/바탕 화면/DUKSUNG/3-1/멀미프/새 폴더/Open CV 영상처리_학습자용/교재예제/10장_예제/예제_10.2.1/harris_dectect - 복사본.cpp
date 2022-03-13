#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void cornerharris_eigen(Mat image, Mat& corner, int blockSize, int ksize, float k)
{
	corner = Mat(image.size(), CV_32F, Scalar(0));
	Mat resp = Mat::zeros(image.size(), CV_32FC(6));

	Mat a1(image.size(), CV_32F, Scalar(0));;
	Mat a2(image.size(), CV_32F, Scalar(0));;
	Mat a3(image.size(), CV_32F, Scalar(0));;
	Mat a4(image.size(), CV_32F, Scalar(0));;

	cornerEigenValsAndVecs(image, resp, blockSize, ksize, BORDER_DEFAULT);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++)
		{
			float l1 = resp.at<Vec6f>(i, j)[0];
			float l2 = resp.at<Vec6f>(i, j)[1];
			corner.at<float>(i, j) = l1*l2 - k * (l1 + l2) * (l1 + l2);

			a1.at<float>(i,j)= resp.at<Vec6f>(i, j)[2];
			a2.at<float>(i, j) = resp.at<Vec6f>(i, j)[3];
			a3.at<float>(i, j) = resp.at<Vec6f>(i, j)[4];
			a4.at<float>(i, j) = resp.at<Vec6f>(i, j)[5];
		}
	}
}


void cornerharris2(Mat image, Mat& corner, int blockSize, int ksize, float k)
{
	Mat dx, dy;
	Mat dx2(image.size(), CV_32F, Scalar(0));
	Mat dy2(image.size(), CV_32F, Scalar(0));
	Mat dxy(image.size(), CV_32F, Scalar(0));

	corner = Mat(image.size(), CV_32F, Scalar(0));

	for (int i = 1; i < image.rows-1; i++) {
		for (int j = 1; j < image.cols-1; j++) {

			float tx = 
					image.at<uchar>(i + 1, j - 1) + image.at<uchar>(i + 1, j) + image.at<uchar>(i + 1, j + 1)
				- image.at<uchar>(i - 1, j - 1)	- image.at<uchar>(i - 1, j)	- image.at<uchar>(i - 1, j + 1);

			float ty =
				image.at<uchar>(i - 1, j + 1) + image.at<uchar>(i, j + 1) + image.at<uchar>(i + 1, j + 1)
				- image.at<uchar>(i - 1, j - 1) - image.at<uchar>(i, j - 1) - image.at<uchar>(i + 1, j - 1);

			tx /= 6;
			ty /= 6;

			dx2.at<float>(i, j) = tx* tx;
			dy2.at<float>(i, j) = ty* ty;
			dxy.at<float>(i, j) = tx* ty;
		}
	}

	float g[25] = {
		1, 4, 6, 4, 1,
		4,16,24,16, 4,
		6,24,36,24, 6,
		4,16,24,16, 4,
		1, 4, 6, 4, 1
	};

	Mat ker(5, 5, CV_32F, g);
	ker /= 256;

	filter2D(dx2, dx2, CV_32F, ker);
	filter2D(dy2, dy2, CV_32F, ker);
	filter2D(dxy, dxy, CV_32F, ker);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++)
		{
			float  a = dx2.at<float>(i, j);
			float  b = dy2.at<float>(i, j);
			float  c = dxy.at<float>(i, j);

			float det = (a * b - c * c);
			float trace2 = (a + b) * (a + b);
			corner.at<float>(i, j) = det - k * trace2;
		}
	}

	cout << dx2(Rect(10, 10, 10, 10)) << endl;

	//	cout << "구현 : " << mean(corner) << endl;
}


void cornerharris(Mat image, Mat& corner, int blockSize, int ksize, float k)
{
	Mat dx, dy;
	Mat dx2(image.size(), CV_32F, Scalar(0));
	Mat dy2(image.size(), CV_32F, Scalar(0));
	Mat dxy(image.size(), CV_32F, Scalar(0));

	corner = Mat(image.size(), CV_32F, Scalar(0));

	Sobel(image, dx, CV_32F, 1, 0, ksize);
	Sobel(image, dy, CV_32F, 0, 1, ksize);

	multiply(dx, dx, dx2);
	multiply(dy, dy, dy2);
	multiply(dx, dy, dxy);

	Size msize(5, 5);
	GaussianBlur(dx2, dx2, msize, 0);
	GaussianBlur(dy2, dy2, msize, 0);
	GaussianBlur(dxy, dxy, msize, 0);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++)
		{
			float  a = dx2.at<float>(i, j);
			float  b = dy2.at<float>(i, j);
			float  c = dxy.at<float>(i, j);

			float det = (a * b - c * c);
			float trace2 = (a + b) * (a + b);
			corner.at<float>(i, j) = det - k * trace2;
		}
	}
}

void draw_coner(Mat corner, Mat& image, int thresh)
{
	int cnt = 0;

	double minv, maxv;
	minMaxLoc(corner, &minv, &maxv);
	cout << format("%10.5f %10.5f\n", minv, maxv);

	normalize(corner, corner, 0, 1000, CV_MINMAX, CV_32FC1, Mat());

	cout << mean(corner) << endl;

	//cout << corner(Rect(10, 10, 10, 10)) << endl;

	for (int i = 1; i < corner.rows - 1; i++) {
		for (int j = 1; j < corner.cols - 1; j++)
		{
			float cur = corner.at<float>(i, j);
			if (cur > thresh)
			{
				if (cur > corner.at<float>(i - 1, j) &&
					cur > corner.at<float>(i + 1, j) &&
					cur > corner.at<float>(i, j - 1) &&
					cur > corner.at<float>(i, j + 1)) {

					circle(image, Point(j, i), 1, Scalar(0,0,255), -1);
					cnt++;
				}
			}
		}
	}
	cout << "코너수: " << cnt << endl;
}

Mat image, corner1, corner2, corner3;
int  thresh;

void cornerHarris_demo(int, void*)
{
	Mat img1 = image.clone();
	Mat img2 = image.clone();
	draw_coner(corner1, img1, thresh);
	draw_coner(corner2, img2, thresh);

	imshow("img1-haris", img1);
	imshow("img2-OpenCV harris", img2);
}

int main()
{
	image = imread("../image/harris_test.jpg", 1);
	CV_Assert(image.data);

	int blockSize = 2;
	int apertureSize = 3;
	float k = 0.04f;
	thresh = 50;
	Mat gray;
	
//	resize(image, image , Size(200,200));

	cvtColor(image, gray, CV_BGR2GRAY);

	//	cornerharris_eigen(gray, corner1, blockSize, apertureSize, k);
	cornerharris(gray, corner1, blockSize, apertureSize, k);
	cornerharris2(gray, corner2, blockSize, apertureSize, k);

	imshow("image", image);
	createTrackbar("Threshold: ", "image", &thresh, 1000, cornerHarris_demo);

	cornerHarris_demo(0, 0);
	waitKey();
}