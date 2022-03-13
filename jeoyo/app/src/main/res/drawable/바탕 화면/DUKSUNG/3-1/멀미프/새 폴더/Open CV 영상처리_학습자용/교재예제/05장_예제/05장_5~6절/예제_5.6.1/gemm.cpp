#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Matx23f src1(1, 2, 3, 4, 5, 1); 
	Matx23f src2(5, 4, 2, 3, 2, 1);
	Matx32f src3(5, 4, 2, 3, 2, 1);
	Mat dst1, dst2, dst3;
	double alpha = 1.0, beta = 1.0;

	// 행렬 곱 수행
	gemm(src1, src2, alpha, Mat(), beta, dst1, GEMM_1_T);
	gemm(src1, src2, alpha, noArray(), beta, dst2, GEMM_2_T);
	gemm(src1, src3, alpha, noArray(), beta, dst3);

	// 콘솔창에 출력
	cout << "[src1] = " << endl << src1 << endl;
	cout << "[src2] = " << endl << src2 << endl;
	cout << "[src3] = " << endl << src3 << endl << endl;

	cout << "[dst1] = " << endl << dst1 << endl;
	cout << "[dst2] = " << endl << dst2 << endl;
	cout << "[dst3] = " << endl << dst3 << endl;
	return 0;
}