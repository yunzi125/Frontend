#include "preprocess.hpp"
#include "histogram.hpp"
#include "classify.hpp"
#include "utils.hpp"

int main()
{
	int coin_no, hue_bin = 32;
	cout << "동전 영상번호: ";
	cin >> coin_no;
	String  fname = format("../image/%2d.png", coin_no);
	Mat  image = imread(fname, 1);
	CV_Assert(image.data);

	Mat th_img = preprocessing(image);							// 전처리 – 명암도 변환 및 이진화
	vector<RotatedRect> circles = find_coins(th_img);			// 동전 영역 검색
	vector<Mat> coins_img = make_coinImg(image, circles);		// 동전영상 생성
	vector<Mat> coins_hist = calc_coin_histo(coins_img, hue_bin);// 색상 히스토그램

	int  Ncoins[4] = { 0 };
	vector<int> groups = grouping(coins_hist);					// 동전영상 그룹 분리
	classify_coins(circles, groups, Ncoins);					// 동전 인식 
	int coin_count = calc_coins(Ncoins);						// 금액 계산

																// 결과 출력
	String str = format("total coin: %d Won", coin_count);		// 계산 금액 문자열
	cout << str << endl;											// 콘솔창에 출력
	putText(image, str, Point(10, 50), 1, 2, Scalar(0, 200, 0), 2);	// 영상에 텍스트 쓰기
	
	draw_circle(image, circles, groups);
	imshow("동전영상", image);
	waitKey();
	return 0;
}



