#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int  main()
{
	// 기본 선언 방법
	Matx<int, 3, 3> 	 m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
	Matx<float, 2, 3>	 m2(1, 2, 3, 4, 5, 6);
	Matx<double, 3, 5> m3(3, 4, 5, 7);

	// 간편 선언 방법
	Matx23d  m4(3, 4, 5, 6, 7, 8);
	Matx34d  m5(1, 2, 3, 10, 11, 12, 13, 14, 15);
	Matx66f  m6(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

	// 행렬 원소 접근
	cout << "m5(0, 0) =" << m5(0, 0) << " m5(1, 0) =" << m5(1, 0) << endl;
	cout << "m6(0, 1) =" << m6(0, 1) << " m6(1, 3) =" << m6(1, 3) << endl << endl;

	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m5] = " << endl << m5 << endl;
	cout << "[m6]= " << endl << m6 << endl;
	return 0;
}