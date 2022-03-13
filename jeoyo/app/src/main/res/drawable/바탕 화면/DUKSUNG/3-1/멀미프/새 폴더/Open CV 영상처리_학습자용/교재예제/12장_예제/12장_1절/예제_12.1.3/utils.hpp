vector<Mat>  make_coinImg(const Mat src, vector<RotatedRect> circles)
{
	vector <Mat> coins;
	for (int i = 0; i< (int)circles.size(); i++)
	{
		int    radius = (int)circles[i].angle;
		Size    size = circles[i].size * 1.5f;
		Point2f center = size / 2;

		Mat coin, mask(size, CV_8UC3, Scalar(0, 0, 0));
		circle(mask, center, radius, Scalar(255, 255, 255), FILLED);

		getRectSubPix(src, size, circles[i].center, coin);
		bitwise_and(coin, mask, coin);

		coins.push_back(coin);
		//imshow(format("coin_%0d", i), coin);
		//imshow(format("mask_%0d", i), mask);
	}
	return  coins;
}

void  draw_circle(Mat& image, vector<RotatedRect> circles, vector<int> groups)
{
	Scalar color[] = {
		Scalar(0,  0, 255) , Scalar(255, 0 , 0) ,			// 그룹색상 (빨간색, 파란색)
		Scalar(200, 50, 0) , Scalar(250, 0 ,255)			// 검출순번, 동전반지름 색상
	};

	for (int i = 0; i < (int)circles.size(); i++)
	{
		int  radius = cvRound(circles[i].angle);				// 동전 반지름
		Point center = (Point)circles[i].center;				// 동전 중심
		circle(image, center, radius, color[groups[i]], 2);

		putText(image, to_string(i), center + Point(-10, 0), 1, 1, color[2], 2);			// 검출순번
		putText(image, to_string(radius), center + Point(-10, 20), 1, 1, color[3], 2);// 동전반지름
	}
}