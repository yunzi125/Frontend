#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void calc_histo(const Mat& img, Mat& hist, Vec3i bins, Vec3f range, int _dims)
{
	int		channels[] = { 0, 1, 2 };
	int		histSize[] = { bins[0], bins[1], bins[2] };

	float  range1[] = { 0, range[0] };
	float  range2[] = { 0, range[1] };
	float  range3[] = { 0, range[2] };
	const float* ranges[] = { range1, range2, range3 };

	int dims = (_dims <= 0) ? img.channels() : _dims;// 히스토그램 차원수
	Mat hsv;
	cvtColor(img, hsv, CV_BGR2HSV);						// HSV 컬러 변환

	calcHist(&hsv, 1, channels, Mat(), hist, dims, histSize, ranges);
	normalize(hist, hist, 0, 1, NORM_MINMAX);			// 정규화
}

Mat draw_histo(Mat hist)
{
	if (hist.dims != 2) {
		cout << "히스토그램이 2차원 데이터가 아님니다." << endl;
		exit(1);
	}
	float ratio_value = 512;
	float ratio_hue = 180.f / hist.rows;
	float ratio_sat = 256.f / hist.cols;

	Mat graph(hist.size(), CV_32FC3);
	for (int i = 0; i < hist.rows; i++) {
		for (int j = 0; j < hist.cols; j++)
		{
			float value = hist.at<float>(i, j) * ratio_value;
			float hue = i * ratio_hue;
			float sat = j * ratio_sat;
			graph.at<Vec3f>(i, j) = Vec3f(hue, sat, value);
		}
	}

	graph.convertTo(graph, CV_8U);
	cvtColor(graph, graph, CV_HSV2BGR);
	resize(graph, graph, Size(0, 0), 10, 10, INTER_NEAREST);

	return graph;
}

vector<Mat> load_histo(Vec3i div, Vec3f ranges)
{
	vector<Mat> DB_hists;
	int img_cnt = 0;
	for (int i = 0; i < 100; i++)
	{
		String  fname = format("../image/DB/img_%02d.jpg", i);
		Mat hist, img = imread(fname, IMREAD_COLOR);

		if (!img.empty()) {
			calc_histo(img, hist, div, ranges, 2);
			img_cnt++;
		}
		DB_hists.push_back(hist);
	}

	cout << format( "%d 개의 파일을 로드 및 히스토그램 계산 완료", img_cnt) << endl;
	return DB_hists;	
}

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
	Vec3i divs(30, 42, 0);
	Vec3f ranges(180, 256, 0);
	vector<Mat> DB_hists = load_histo(divs, ranges);
	Mat query = query_img();

	Mat  hs_hist;
	calc_histo(query, hs_hist, divs, ranges, 2);
	Mat hist_img = draw_histo(hs_hist);

	imshow("image", query);
	imshow("hist_img", hist_img);
	waitKey();

	return 0;
}