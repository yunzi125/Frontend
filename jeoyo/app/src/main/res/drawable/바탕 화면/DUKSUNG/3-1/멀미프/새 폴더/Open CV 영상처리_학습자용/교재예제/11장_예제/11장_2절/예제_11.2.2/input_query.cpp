#include "histo.hpp"

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

int main()
{
	Vec3i bins(30, 42, 0);
	Vec3f ranges(180, 256, 0);
	vector<Mat> DB_hists = load_histo(bins, ranges, 100);
	Mat query = query_img();

	Mat hsv, query_hist;
	cvtColor(query, hsv, CV_BGR2HSV);					// HSV 컬러 변환
	calc_Histo(hsv, query_hist, bins, ranges, 2);		// 2차원 히스토그램 계산
	Mat hist_img = draw_histo(query_hist);				// 2차원 그래프

	imshow("query", query);
	imshow("hist_img", hist_img);
//	imshow("query + hist_img", make_img(query, hist_img));
	waitKey();
	return 0;
}