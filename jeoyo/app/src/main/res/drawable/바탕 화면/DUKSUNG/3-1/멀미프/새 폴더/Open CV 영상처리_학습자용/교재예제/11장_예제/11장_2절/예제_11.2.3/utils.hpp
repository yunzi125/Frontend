
Mat query_img()
{
	do {
		int q_no = 74;
		cout << "���� ���� ��ȣ�� �Է��ϼ��� : ";
		cin >> q_no;

		String  fname = format("../image/DB/img_%02d.jpg", q_no);
		Mat query = imread(fname, IMREAD_COLOR);

		if (query.empty())	cout << "���� ���� ��ȣ�� �߸��Ǿ����ϴ�." << endl;
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
	int flag = SORT_EVERY_COLUMN + SORT_DESCENDING; // ����� + ��������
	cv::sort(DB_similaritys, sorted_sim, flag);		// ��� ���Ұ� ����
	sortIdx(DB_similaritys, m_idx, flag);		// ���� ������ ���� �ε��� ��ȯ 

	for (int i = 0; i < (int)sorted_sim.total(); i++)
	{
		double  sim = sorted_sim.at<double>(i);
		if (sim > sinc)
		{
			int idx = m_idx.at<int>(i);				// ���� ������ ���� �ε���
			String  fname = format("../image/DB/img_%02d.jpg", idx);
			Mat img = imread(fname, 1);			// ���� ������ �� �̸����� ���� �б�

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
			cvtColor(img, hsv, CV_BGR2HSV);			// HSV �÷� ��ȯ
			calc_histo(hsv, hist, bins, ranges, 2);			// 2���� ������׷� ���

			Mat hist_img = draw_histo(hist);
			Mat tmp = make_img(img, hist_img);

			String  title = format("img_%03d - %5.2f", idx, sim);
			cout << title << endl;
			imshow(title, tmp);
		}
	}
}
