#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void calc_Histo(const Mat& img, Mat& hist, Vec3i bins, Vec3f range, int _dims)
{
	int dims = (_dims <= 0) ? img.channels() : _dims;// 히스토그램 차원수
	int		channels[] = { 0, 1, 2 };
	int		histSize[] = { bins[0], bins[1], bins[2] };

	float  range1[] = { 0, range[0] };
	float  range2[] = { 0, range[1] };
	float  range3[] = { 0, range[2] };
	const float* ranges[] = { range1, range2, range3 };

	calcHist(&img, 1, channels, Mat(), hist, dims, histSize, ranges);
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

	graph.convertTo(graph, CV_8U);;
	cvtColor(graph, graph, CV_HSV2BGR);
	resize(graph, graph, Size(0, 0), 10, 10, INTER_NEAREST);

	return graph;
}

vector<Mat> load_histo(Vec3i bins, Vec3f ranges, int nImages)
{
	vector<Mat> DB_hists;
	for (int i = 0; i < nImages; i++)
	{
		String  fname = format("../image/DB/img_%02d.jpg", i);
		Mat hsv, hist, img = imread(fname, IMREAD_COLOR);
		if (img.empty()) continue;

		cvtColor(img, hsv, CV_BGR2HSV);			// HSV 컬러 변환
		calc_histo(hsv, hist, bins, ranges, 2);			// 2차원 히스토그램 계산
		DB_hists.push_back(hist);
	}
	cout << format("%d 개의 파일을 로드 및 히스토그램 계산 완료", DB_hists.size()) << endl;
	return DB_hists;
}

