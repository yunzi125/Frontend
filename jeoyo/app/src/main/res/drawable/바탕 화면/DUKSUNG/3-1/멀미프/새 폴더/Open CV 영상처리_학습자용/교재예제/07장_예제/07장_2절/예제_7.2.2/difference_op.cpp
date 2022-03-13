#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void differOp(Mat img, Mat& dst, int mask_size)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	Point h_m(mask_size / 2, mask_size / 2);

	for (int i = h_m.y; i < img.rows - h_m.y; i++){
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			vector<uchar> mask;
			for (int u = 0 ; u < mask_size; u++) {
				for (int v = 0; v < mask_size; v++){
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					mask.push_back(img.at<uchar>(y,x)) ;
				}
			}

			uchar max = 0;
			for (int k = 0; k < (int) mask.size() / 2; k++)
			{
				int start = mask[k];
				int end   = mask[mask.size() - k - 1];

				uchar difference = abs(start - end);
				if (difference > max)  max = difference;
			}
			dst.at<uchar>(i, j) = max;
		}
	}
}

int main()
{
	Mat image = imread("../image/edge_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat edge;
	differOp(image, edge, 3);

	imshow("image", image);
	imshow("edge", edge);
	waitKey();
	return 0;
}

