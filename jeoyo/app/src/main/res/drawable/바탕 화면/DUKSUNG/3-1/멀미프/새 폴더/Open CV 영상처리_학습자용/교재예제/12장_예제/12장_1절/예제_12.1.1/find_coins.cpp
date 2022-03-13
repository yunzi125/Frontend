#include "preprocess.hpp"

int main()
{
	int coin_no = 70;
	String  fname = format("../image/%2d.png", coin_no);
	Mat  image  = imread(fname, 1 );
	CV_Assert(image.data);
	
	Mat th_img = preprocessing(image);
	vector<RotatedRect> circles = find_coins(th_img);

	for (int i = 0; i < circles.size(); i++) 
	{
		float radius = circles[i].angle;
		circle(image, circles[i].center, radius, Scalar(0, 255, 0), 2);
	}

	imshow("전처리영상", th_img);
	imshow("동전영상", image);
	waitKey();

	return 0;
}



