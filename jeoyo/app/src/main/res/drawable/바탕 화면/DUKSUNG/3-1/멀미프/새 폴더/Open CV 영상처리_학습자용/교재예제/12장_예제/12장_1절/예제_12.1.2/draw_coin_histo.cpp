#include "preprocess.hpp"
#include "histogram.hpp"

vector<Mat>  make_coinImg(const Mat src, vector<RotatedRect> circles)
{
	vector <Mat> coins;									// ���� �����
	for (int i = 0; i< (int)circles.size(); i++)
	{
		int    	radius = (int)circles[i].angle;				// ���� ������
		Size	size = circles[i].size * 1.5f;				// ���� ���� ũ�� 1.5��
		Point2f center = size / 2;							// ����ũ �߽�

		Mat coin, mask(size, CV_8UC3, Scalar(0, 0, 0));  // ����ũ ���
		circle(mask, center, radius, Scalar(255, 255, 255), FILLED);

		getRectSubPix(src, size, circles[i].center, coin);		// �������� ��������
		bitwise_and(coin, mask, coin);						// ����ŷ ó��
		coins.push_back(coin);								// �������� ����		
//		imshow(format("mask_%0d", i), mask);				// ����ũ ���� ����
	}
	return  coins;
}

int main()
{
	int coin_no, hue_bin = 32;
	cout << "���� �����ȣ: ";
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

		imshow(format("���� -%2d", i), coins_img[i]);
		imshow(format("������׷� -%2d" , i), hist_img);
	}

	waitKey();
	return 0;
}