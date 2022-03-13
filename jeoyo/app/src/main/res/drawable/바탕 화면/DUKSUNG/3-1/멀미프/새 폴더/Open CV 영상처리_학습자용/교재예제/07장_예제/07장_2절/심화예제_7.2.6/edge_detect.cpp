#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

	int edgeThresh = 1;
	Mat image, gray, edge, cedge;

	// define a trackbar callback
	static void onTrackbar(int, void*)
	{
		blur(gray, edge, Size(3, 3));

		// Run the edge detector on grayscale
		Canny(edge, edge, edgeThresh, edgeThresh * 3, 3);
		cedge = Scalar::all(0);

		image.copyTo(cedge, edge);
		imshow("Edge map", cedge);
	}

	int main(int argc, const char** argv)
	{
		image = imread("../image/edge_test1.jpg", 1);
		CV_Assert(image.data);

		cedge.create(image.size(), image.type());
		cvtColor(image, gray, COLOR_BGR2GRAY);

		namedWindow("Edge map", 1);
		createTrackbar("Canny threshold", "Edge map", &edgeThresh, 100, onTrackbar);
		onTrackbar(0, 0);
		waitKey(0);

		return 0;
	}

