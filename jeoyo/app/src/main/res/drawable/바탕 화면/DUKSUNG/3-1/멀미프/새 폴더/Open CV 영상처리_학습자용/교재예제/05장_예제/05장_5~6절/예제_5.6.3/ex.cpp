#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Matx33f m1(1, 0, 2, -3, 4, 6, -1, -2, 3);
	Matx31f m2(6, 30 , 8); 	
	Mat     m1_inv1, dst1, dst2;

	invert(m1, m1_inv1, DECOMP_LU);
	dst1 = m1_inv1 * (Mat)m2;
	solve(m1, m2, dst2, DECOMP_LU);

	cout << "[m1_inv1] = " << endl << m1_inv1 << endl << endl;
	cout << "[dst1] = " << dst1.t() << endl;
	cout << "[dst2] = " << dst2.t() << endl;
	return 0;
}