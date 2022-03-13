#include "preprocess.hpp"
#include "candiate.hpp"

int main()
{ 
	int car_no;
	cout << "차량 영상 번호 (0-20) : ";
	cin >> car_no;

	string fn = format("../image/test_car/%02d.jpg", car_no);
	Mat image = imread(fn, 1);
	CV_Assert(image.data);

	Mat morph = preprocessing(image);
	vector<RotatedRect> candidates;
	find_candidates(morph, candidates);

	vector<Mat> candidate_img = make_candidates(image, candidates);

	// 후보영상 표시 
	for (int i = 0; i < candidate_img.size(); i++) {
		imshow("후보영상- " + to_string(i), candidate_img[i]);
		resizeWindow("후보영상- " + to_string(i), 200, 40);		//윈도우 크기 조정
	}
	imshow("image - " + to_string(car_no), image);
	waitKey();
	return 0;
}