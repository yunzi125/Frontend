#include "preprocess.hpp"
#include "histogram.hpp"

vector<Mat>  make_coinImg(const Mat src, vector<RotatedRect> circles)
{
	vector <Mat> coins;									// 동전 영상들
	for (int i = 0; i< (int)circles.size(); i++)
	{
		int    	radius = (int)circles[i].angle;				// 동전 반지름
		Size	size = circles[i].size * 1.5f;				// 검출 동전 크기 1.5배
		Point2f center = size / 2;							// 마스크 중심

		Mat coin, mask(size, CV_8UC3, Scalar(0, 0, 0));  // 마스크 행렬
		circle(mask, center, radius, Scalar(255, 255, 255), FILLED);

		getRectSubPix(src, size, circles[i].center, coin);		// 동영영상 가져오기
		bitwise_and(coin, mask, coin);						// 마스킹 처리
		coins.push_back(coin);								// 동전영상 저장		
//		imshow(format("mask_%0d", i), mask);				// 마스크 영상 보기
	}
	return  coins;
}

int main()
{
	int coin_no, hue_bin = 32;
	cout << "동전 영상번호: ";
	cin >> coin_no;
	String  fname = format("../image/%2d.png", coin_no);
	Mat  image = imread(fname, 1);
	CV_Assert(image.data);

	Mat th_img = preprocessing(image);
	vector<RotatedRect> circles = find_coins(th_img);
	vector<Mat> coins_img  = make_coinImg(image, circles);
	vector<Mat> coins_hist = calc_coin_histo(coins_img, hue_bin);

	for (int i = 0; i < coins_img.size(); i++) 
	{
		Mat hist_img;
		draw_histo_hue(coins_hist[i], hist_img, Size(256, 150));

		imshow(format("동전 -%2d", i), coins_img[i]);
		imshow(format("히스토그램 -%2d" , i), hist_img);
	}

	waitKey();
	return 0;
}