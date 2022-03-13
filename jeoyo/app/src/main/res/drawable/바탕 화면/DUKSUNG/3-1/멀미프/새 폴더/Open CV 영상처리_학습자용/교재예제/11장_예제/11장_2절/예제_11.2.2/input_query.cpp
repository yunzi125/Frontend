#include "histo.hpp"

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

int main()
{
	Vec3i bins(30, 42, 0);
	Vec3f ranges(180, 256, 0);
	vector<Mat> DB_hists = load_histo(bins, ranges, 100);
	Mat query = query_img();

	Mat hsv, query_hist;
	cvtColor(query, hsv, CV_BGR2HSV);					// HSV �÷� ��ȯ
	calc_Histo(hsv, query_hist, bins, ranges, 2);		// 2���� ������׷� ���
	Mat hist_img = draw_histo(query_hist);				// 2���� �׷���

	imshow("query", query);
	imshow("hist_img", hist_img);
//	imshow("query + hist_img", make_img(query, hist_img));
	waitKey();
	return 0;
}