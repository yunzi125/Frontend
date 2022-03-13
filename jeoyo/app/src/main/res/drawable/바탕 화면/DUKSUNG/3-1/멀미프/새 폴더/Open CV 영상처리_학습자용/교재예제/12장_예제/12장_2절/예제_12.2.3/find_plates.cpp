#include "preprocess.hpp"

void draw_rotatedRect(Mat &img, RotatedRect mr, Scalar color, int thickness = 2)
{
	Point2f  pts[4];
	mr.points(pts);

	for (int i = 0; i <4; ++i) {
		line(img, pts[i], pts[(i + 1) % 4], color, thickness);
	}
}


bool key_check(int& no)
{
	int key = waitKey(0);							// Ű�̺�Ʈ ���
	if (key == 2621440) 		no++;				// �Ʒ� ȭ��ǥŰ�̸� ���� ����
	else if (key == 2490368) 	no--;				// �� ȭ��ǥŰ�̸� ���� ����
	else if (key == 32 || key == 27)	return false;	// ���α׷� ���� ����

	return true;
}


int main()
{
	int car_no = 1;
	cout << "���� ���� ��ȣ (0-20) : ";
	cin >> car_no;

	string fn = format("../image/test_car/%02d.jpg", car_no);
	Mat image = imread(fn, 1);
	CV_Assert(image.data);

	Mat  morph = preprocessing(image);	
	vector<RotatedRect> candidates;				// ��ȣ�� �ĺ� ����
	find_candidates(morph, candidates);			// �ĺ����� ����

	for (int i = 0; i < (int)candidates.size(); i++) {
		draw_rotatedRect(image, candidates[i], Scalar(0, 255, 0), 2);
	}

	if (candidates.size() == 0)
		cout << "��ȣ�� �ĺ������� �������� ���Ͽ����ϴ�. " << endl;

	imshow("image", image);
	waitKey();
	return 0;
}
