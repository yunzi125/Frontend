#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("../image/minMax.jpg", IMREAD_GRAYSCALE);
	
	double minVal, maxVal;
	minMaxIdx(image, &minVal, &maxVal);

	double ratio = (maxVal - minVal)/ 255.0 ;
	Mat  dst = (image - minVal) / ratio;

	cout << "�ּҰ�  = " << minVal << endl; 
	cout << "�ִ밪  = " << maxVal << endl;

	imshow("image", image);
	imshow("dst" , dst );
	waitKey();
	return 0;
}






