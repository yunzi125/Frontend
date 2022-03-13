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
	cout <<  "      ���� �簢�� ���� " << endl;
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < pts.rows; i++)
	{
		Point pt1(pts(i, 0), pts(i, 1));	// �簢�� ������ǥ
		Point pt2(pts(i, 2), pts(i, 3));	// �簢�� ������ǥ
		rects.push_back(Rect(pt1, pt2));	// ���� ����
		
		sizes.push_back(rects[i].area());	// �簢�� ũ�� ����
		cout << format("rects[%d] = ", i) << rects[i] << endl;
	}
	
	// ���� ��, ���� ������ ���� ��ǥ ��ȯ
	sortIdx(sizes, sort_idx, SORT_EVERY_COLUMN);

	cout << endl<<  " ũ��� ���� �簢�� ���� \tũ��" << endl;
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < rects.size(); i++) {
		int idx = sort_idx(i);

		cout << rects[idx] << "\t" << sizes(idx) << endl;
	}
	cout << "----------------------------------------" << endl;
	return 0;
}