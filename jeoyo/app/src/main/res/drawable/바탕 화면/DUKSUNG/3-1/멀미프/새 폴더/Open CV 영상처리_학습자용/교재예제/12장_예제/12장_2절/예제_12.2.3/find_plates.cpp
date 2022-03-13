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
	int key = waitKey(0);							// 키이벤트 대기
	if (key == 2621440) 		no++;				// 아래 화살표키이면 다음 영상
	else if (key == 2490368) 	no--;				// 윗 화살표키이면 이전 영상
	else if (key == 32 || key == 27)	return false;	// 프로그램 종료 조건

	return true;
}


int main()
{
	int car_no = 1;
	cout << "차량 영상 번호 (0-20) : ";
	cin >> car_no;

	string fn = format("../image/test_car/%02d.jpg", car_no);
	Mat image = imread(fn, 1);
	CV_Assert(image.data);

	Mat  morph = preprocessing(image);	
	vector<RotatedRect> candidates;				// 번호판 후보 영역
	find_candidates(morph, candidates);			// 후보영역 검출

	for (int i = 0; i < (int)candidates.size(); i++) {
		draw_rotatedRect(image, candidates[i], Scalar(0, 255, 0), 2);
	}

	if (candidates.size() == 0)
		cout << "번호판 후보영역을 검출하지 못하였습니다. " << endl;

	imshow("image", image);
	waitKey();
	return 0;
}
