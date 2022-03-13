#include "preprocess.hpp"					// 전처리 및 후보영역 검출 함수
#include "candiate.hpp"						// 후보영역 개선 및 후보영상 생성 함수
#include "SVM.hpp"						// 학습데이터 로드 및 SVM 수행
#include "kNN.hpp"						// kNN 학습 함수 – 10장 3절
#include "classify_objects.hpp"			// kNN 분류 함수

int main()
{
	int K1 = 15  , K2 = 15;
	Ptr<ml::KNearest> knn[2];
	knn[0] = kNN_train("../image/trainimage/train_numbers2001.png", K1, 10, 20);
	knn[1] = kNN_train("../image/trainimage/train_texts.png", K2, 25, 20);

	// 	학습된 데이터 로드
	Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("../SVMtrain.xml");

	int car_no;
	cout << "차량 영상 번호 (0-20) : ";
	cin >> car_no;
	string fn = format("../image/test_car/%02d.jpg", car_no);
	Mat image = imread(fn, 1);
	CV_Assert(image.data);

	Mat morph = preprocessing(image);								// 전처리
	vector<RotatedRect> candidates;
	find_candidates(morph, candidates);									// 후보 영역 검출
	vector<Mat> candidate_img = make_candidates(image, candidates);// 후보 영상 생성

	int plate_no = classify_plates(svm , candidate_img);			// SVM 분류

	if (plate_no >= 0) 
	{
		vector <Rect> obejct_rects, sorted_rects;
		vector <Mat> numbers;							// 숫자 객체 
		Mat  plate_img, color_plate;								// 컬러 번호판 영상 

		preprocessing_plate(candidate_img[plate_no], plate_img);	// 번호판 영상 전처리
		cvtColor(plate_img, color_plate, CV_GRAY2BGR);

		find_objects(~plate_img, obejct_rects);		// 숫자 및 문자 검출  

		sort_rects(obejct_rects, sorted_rects);			// 검출객체 정렬(x 좌표기준)

		for (size_t i = 0; i < sorted_rects.size(); i++) 
		{
			numbers.push_back(plate_img(sorted_rects[i]));	// 정렬된 숫자 영상
			rectangle(color_plate, sorted_rects[i], Scalar(0, 0, 255), 1); // 사각형 그리기
		}

		if (numbers.size() == 7) {
			classify_numbers(numbers, knn, K1, K2);		// kNN 분류 수행
		}
		else  cout << "숫자(문자) 객체를 정확히 검출하지 못했습니다." << endl;

		imshow("번호판 영상", color_plate);					// 번호판 영상 표시
		draw_rotatedRect(image, candidates[plate_no], Scalar(0, 0, 255), 2);
	}
	else  cout << "번호판을 검출하지 못하였습니다. " << endl;

	imshow("image", image);
	waitKey();
	return 0;
}

