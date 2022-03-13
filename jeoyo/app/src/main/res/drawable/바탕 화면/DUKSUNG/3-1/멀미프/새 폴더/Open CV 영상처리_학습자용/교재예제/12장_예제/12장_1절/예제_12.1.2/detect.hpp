Mat  preprocessing(Mat img)
{
	Mat gray, th_img;
	cvtColor(img, gray, CV_BGR2GRAY);
	GaussianBlur(gray, gray, Size(7, 7), 2, 2);

	threshold(gray, th_img, 130, 255, THRESH_BINARY | THRESH_OTSU);
	morphologyEx(th_img, th_img, MORPH_OPEN, Mat(), Point(-1, -1), 1);

	return th_img;
}

vector<RotatedRect>  find_coins(Mat img)
{
	vector<vector<Point> > contours;
	findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<RotatedRect> circles;
	for (int i = 0; i< (int)contours.size(); i++)
	{
		RotatedRect  mr = minAreaRect(contours[i]);
		mr.angle = (mr.size.width + mr.size.height) / 4.0f;

		if (mr.angle > 18) circles.push_back(mr);
	}
	return circles;
}

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


Mat  draw_circle(Mat src, vector<RotatedRect> circles, vector<int> groups)
{
	Mat image = src.clone();
	Scalar color[] = { Scalar(0, 0,255) , Scalar(255,0,0) ,
		Scalar(200, 0, 0) , Scalar(200,0,200)
	};

	for (int i = 0; i < (int)circles.size(); i++)
	{
		int     radius = cvRound(circles[i].angle);
		Point center = (Point)circles[i].center;
		circle(image, center, radius, color[groups[i]], 2);

		putText(image, to_string(i), center + Point(-10, 0), 1, 1, color[2], 2);
		putText(image, to_string(radius), center + Point(-10, 20), 1, 1, color[3], 2);
	}
	return image;
}