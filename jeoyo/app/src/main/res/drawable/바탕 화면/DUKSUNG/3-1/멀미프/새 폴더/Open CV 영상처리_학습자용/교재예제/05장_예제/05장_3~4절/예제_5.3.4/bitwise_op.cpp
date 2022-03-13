#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image1(250, 250, CV_8U, Scalar(0)) ;
	Mat image2(250, 250, CV_8U, Scalar(0));
	Mat image3, image4, image5, image6;

	Point center = image1.size() / 2;
	circle(image1, center, 80, Scalar(255), -1);		// �߽ɿ� �� �׸���
	rectangle(image2, Point(0,0), Point(125,250), Scalar(255), -1);
	
	// ��Ʈ ����
	bitwise_or(image1, image2, image3);
	bitwise_and(image1, image2, image4);
	bitwise_xor(image1, image2, image5);
	bitwise_not(image1, image6);

	imshow("image1", image1);
	imshow("image2", image2);
	imshow("bitwise_or", image3);
	imshow("bitwise_and", image4);
	imshow("bitwise_xor", image5);
	imshow("bitwise_not", image6);
	waitKey();
	return 0;
}