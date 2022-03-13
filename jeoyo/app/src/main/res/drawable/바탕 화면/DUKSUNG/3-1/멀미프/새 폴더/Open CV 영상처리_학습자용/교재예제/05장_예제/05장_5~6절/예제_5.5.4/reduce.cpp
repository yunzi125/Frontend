#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Matx<ushort, 5, 4>  pts;
	Mat_<int> sizes, sort_idx;
	vector<Rect> rects;
	randn(pts, Scalar(200), Scalar(100));

	cout << "----------------------------------------" << endl;
	cout <<  "      랜덤 사각형 정보 " << endl;
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < pts.rows; i++)
	{
		Point pt1(pts(i, 0), pts(i, 1));	// 사각형 시작좌표
		Point pt2(pts(i, 2), pts(i, 3));	// 사각형 종료좌표
		rects.push_back(Rect(pt1, pt2));	// 벡터 저장
		
		sizes.push_back(rects[i].area());	// 사각형 크기 저장
		cout << format("rects[%d] = ", i) << rects[i] << endl;
	}
	
	// 정렬 후, 정렬 원소의 원본 좌표 반환
	sortIdx(sizes, sort_idx, SORT_EVERY_COLUMN);

	cout << endl<<  " 크기순 정렬 사각형 정보 \t크기" << endl;
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < rects.size(); i++) {
		int idx = sort_idx(i);

		cout << rects[idx] << "\t" << sizes(idx) << endl;
	}
	cout << "----------------------------------------" << endl;
	return 0;
}