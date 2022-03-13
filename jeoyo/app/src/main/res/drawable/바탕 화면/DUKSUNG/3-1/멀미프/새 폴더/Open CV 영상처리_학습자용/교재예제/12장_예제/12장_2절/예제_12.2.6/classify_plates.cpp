#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;
using namespace std;

#include "find_plates.hpp"


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
	int no = 0;
	do {
		destroyAllWindows();
		string fn = format("../image/test_car/%02d.jpg", no);
		Mat image = imread(fn, 1);
		CV_Assert(image.data);

		Mat morph, plate_img;
		preprocessing(image, morph);
		vector<RotatedRect> candidates;
		find_candidates(morph, candidates);

		vector<Mat> candidate_img = make_candidates(image, candidates);

		imshow("image - " + to_string(no), image);

	}
	while (key_check(no));

	return 0; 
}

