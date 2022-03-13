
Mat query_img()
{
	do {
		int q_no = 74;
		cout << "질의 영상 번호를 입력하세요 : ";
		cin >> q_no;

		String  fname = format("../image/DB/img_%02d.jpg", q_no);
		Mat query = imread(fname, IMREAD_COLOR);

		if (query.empty())	cout << "질의 영상 번호가 잘못되었습니다." << endl;
		else 				return query;
	} while (1);
}

Mat calc_similarity(Mat query_hist, vector<Mat>& DB_hists)
{
	Mat DB_similaritys;

	for (int i = 0; i < (int)DB_hists.size(); i++)
	{
		double compare = compareHist(query_hist, DB_hists[i], CV_COMP_CORREL);
		DB_similaritys.push_back(compare);
	}

	return DB_similaritys;
}

void select_view(double sinc, Mat DB_similaritys)
{
	Mat m_idx, sorted_sim;
	int flag = SORT_EVERY_COLUMN + SORT_DESCENDING; // 행단위 + 내림차순
	cv::sort(DB_similaritys, sorted_sim, flag);		// 행렬 원소값 정렬
	sortIdx(DB_similaritys, m_idx, flag);		// 정렬 원소의 원본 인덱스 반환 

	for (int i = 0; i < (int)sorted_sim.total(); i++)
	{
		double  sim = sorted_sim.at<double>(i);
		if (sim > sinc)
		{
			int idx = m_idx.at<int>(i);				// 정렬 원소의 원본 인덱스
			String  fname = format("../image/DB/img_%02d.jpg", idx);
			Mat img = imread(fname, 1);			// 정렬 원소의 원 이름으로 영상 읽기

			String  title = format("img_%03d - %5.2f", idx, sim);
			cout << title << endl;
			imshow(title, img);
		}
	}
}

Mat make_img( Mat img, Mat hist_img)
{
	int w = img.cols + hist_img.cols + 10;
	int h = max(img.rows, hist_img.rows);
	Mat tmp(h, w, CV_8UC3, Scalar(255, 255, 255));

	int gap = abs(img.rows-hist_img.rows)/2;

	Rect r1(Point(0, 0), img.size());
	Rect r2(Point(img.cols + 5, gap), hist_img.size());

	img.copyTo(tmp(r1));
	hist_img.copyTo(tmp(r2));

	return tmp;
}

void select_view(double sinc, Mat DB_similaritys, Vec3i bins, Vec3f ranges)
{
	Mat m_idx, sorted_sim;
	sortIdx(DB_similaritys, m_idx, SORT_EVERY_COLUMN + SORT_DESCENDING);
	cv::sort(DB_similaritys, sorted_sim, SORT_EVERY_COLUMN + SORT_DESCENDING);

	for (int i = 0; i < (int)sorted_sim.total(); i++)
	{
		double  sim = sorted_sim.at<double>(i);
		if (sim > sinc)
		{
			int idx = m_idx.at<int>(i);
			String  fname = format("../image/DB/img_%02d.jpg", idx);
			Mat img = imread(fname, 1);

			Mat  hsv, hist;
			cvtColor(img, hsv, CV_BGR2HSV);			// HSV 컬러 변환
			calc_histo(hsv, hist, bins, ranges, 2);			// 2차원 히스토그램 계산

			Mat hist_img = draw_histo(hist);
			Mat tmp = make_img(img, hist_img);

			String  title = format("img_%03d - %5.2f", idx, sim);
			cout << title << endl;
			imshow(title, tmp);
		}
	}
}
