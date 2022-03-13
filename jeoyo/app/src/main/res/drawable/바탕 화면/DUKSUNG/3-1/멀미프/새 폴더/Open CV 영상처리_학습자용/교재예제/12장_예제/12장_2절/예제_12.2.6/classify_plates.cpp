#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;
using namespace std;

#include "find_plates.hpp"


bool key_check(int& no)
{
	int key = waitKey(0);							// 키이벤트 대기
	if (key == 2621440) 		no++;				// 아래 화살표키이면 다음 영상
	else if (key == 2490368) 	no--;				// 윗 화살표키이면 이전 영상
	else if (key == 32 || key == 27)	return false;	// 프로그램 종료 조건

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

