#include <opencv2/opencv.hpp>

int  main()
{
	// Point_ 객체 선언 방식
	cv::Point_<int> pt1(100, 200);
	cv::Point_<float> pt2(92.3f, 125.23f);
	cv::Point_<double> pt3(100.2, 300.9);

	// Point_ 객체 간결 선언 방식
	cv::Point2i  pt4(120, 69);
	cv::Point2f  pt5(0.3f, 0.f), pt6(0.f, 0.4f);
	cv::Point2d  pt7(0.25, 0.6);

	// Point_ 객체 연산 
	cv::Point    pt8 = pt1 + (cv::Point) pt2;
	cv::Point2f  pt9 = pt6 * 3.14f;
	cv::Point2d  pt10 = (pt3 + (cv::Point2d) pt6) * 10;

	std::cout << "pt8 = " << pt8.x << " , " << pt8.y << std::endl;
	std::cout << "[pt9] = " << pt9 << std::endl;
	std::cout << (pt2 == pt6) << std::endl;
	std::cout << "pt7과 pt8의 내적 : " << pt7.dot(pt8) << std::endl;
	return 0;
}