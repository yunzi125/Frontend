Mat  make_palatte(int rows)
{
	Mat hsv(rows, 1, CV_8UC3);
	for (int i = 0; i < rows; i++)
	{
		uchar hue = saturate_cast<uchar>((float)i / rows * 180);
		hsv.at<Vec3b>(i) = Vec3b(hue, 255, 255);
	}
	cvtColor(hsv, hsv, CV_HSV2BGR);
	return hsv;
}
// 색상으로 히스토그램 그리기
void draw_histo_hue(Mat hist, Mat &hist_img, Size size = Size(256, 200))
{
	Mat hsv_palatte = make_palatte(hist.rows);

	hist_img = Mat(size, CV_8UC3, Scalar(255, 255, 255));
	float  bin = (float)hist_img.cols / hist.rows;
	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);

	for (int i = 0; i<hist.rows; i++)
	{
		float start_x = (i * bin);
		float  end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at <float>(i));

		Scalar color = hsv_palatte.at<Vec3b>(i);				// 색상팔레트 색지정
		if (pt2.y>0) rectangle(hist_img, pt1, pt2, color, -1);	// 팔레트 색 그리기	
	}
	flip(hist_img, hist_img, 0);
}

void calc_Histo(const Mat& image, Mat& hist, Vec3i bins, Vec3f range, int _dims)
{
	int dims = (_dims <= 0) ? image.channels() : _dims;			// 히스토그램 차원수
	int		channels[] = { 0, 1, 2 };
	int		histSize[] = { bins[0], bins[1], bins[2] };

	float  range1[] = { 0, range[0] };
	float  range2[] = { 0, range[1] };
	float  range3[] = { 0, range[2] };
	const float* ranges[] = { range1, range2, range3 };

	calcHist(&image, 1, channels, Mat(), hist, dims, histSize, ranges);
}

vector <Mat> calc_coin_histo(vector<Mat> coins, int hue_bin)
{
	vector <Mat> histo;
	for (int i = 0; i < (int)coins.size(); i++)
	{
		Mat hsv, hist, hist_img;
		cvtColor(coins[i], hsv, CV_BGR2HSV);				// 컬러 공간변환
		calc_Histo(hsv, hist, Vec3i(hue_bin, 0, 0), Vec3f(180, 0, 0), 1);

		hist.at<float>(0) = 0;									// 빨간색 빈도 제거
		hist.at<float>(1) = 0;									// 빨간색 빈도 제거
		normalize(hist, hist, 0, 1, NORM_MINMAX);				// 정규화
		histo.push_back(hist);
	}
	return histo;
}