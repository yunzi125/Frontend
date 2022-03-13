#include "kNN.hpp"

int main()
{
	Size  size(40, 40);			// 학습 셀 크기 
	int  K = 15;				// 선출하는 이웃 샘플수
	int  Nclass = 10;			// 인식 숫자(카테고리) 개수
	int  Nsample = 20;		// 숫자당 학습 샘플수

	string image_file = "../image/train_numbers.png";
	Mat  train_image = imread(image_file, 0);		// 영상 로드
	CV_Assert(train_image.data);

	threshold(train_image, train_image, 32, 255, CV_THRESH_BINARY);

	Mat  trainData, classLable;
	for (int i = 0, k = 0; i < Nclass; i++) {
		for (int j = 0; j < Nsample; j++, k++)
		{
			Point start(j * size.width, i * size.height);
			Rect  roi(start, size);
			Mat   part = train_image(roi);			// 숫자 영상 분리

			Mat  num = find_number(part);		// 숫자 영역 영상
			Mat  data = place_middle(num, size);	// 정규화 및 1행데이터 구성
			trainData.push_back(data);		// 학습 데이터 수집
			classLable.push_back(i);		// 레이블링
		}
	}

	Ptr<ml::KNearest>  knn = ml::KNearest::create();
	knn->train(trainData, ml::ROW_SAMPLE, classLable);	// k-NN 학습


	int no;
	cout << "영상번호를 입력하세요: ";
	cin >> no;									// 영상번호 입력

	string demo_file = format("../image/num/%02d.png", no);
	Mat  test_img = imread(demo_file, 0);			// 실험 영상 로드
	CV_Assert(test_img.data);						// 예외처리

	threshold(test_img, test_img, 128, 255, THRESH_BINARY);	// 이진화
	Mat  num = find_number(test_img);				// 숫자객체 검출
	Mat  data = place_middle(num, size);			// 숫자객체 셀 중심 배치 

	Mat result;
	knn->findNearest(data, K, result);				// 숫자 분류 수행

	cout << "분류결과 : " << result.at<float>(0) << endl;
	imshow("test_img", test_img);
	waitKey();
	return 0; 
}