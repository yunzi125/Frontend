#include <opencv2/highgui.hpp>

void  main()
{
	cv::Mat  image(300, 400, CV_8UC1, cv::Scalar(200));
	cv::imshow("���󺸱�", image);
	cv::waitKey(0);
}