#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void calc_Histo(const Mat& img, Mat& hist, Vec3i bins, Vec3f range, int _dims)
{
	int dims = (_dims <= 0) ? img.channels() : _dims;// ������׷� ������
	int		channels[] = { 0, 1, 2 };
	int		histSize[] = { bins[0], bins[1], bins[2] };

	float  range1[] = { 0, range[0] };
	float  range2[] = { 0, range[1] };
	float  range3[] = { 0, range[2] };
	const float* ranges[] = { range1, range2, range3 };

	calcHist(&img, 1, channels, Mat(), hist, dims, histSize, ranges);
	normalize(hist, hist, 0, 1, NORM_MINMAX);			// ����ȭ
}

Mat draw_histo(Mat hist)
{
	if (hist.dims != 2) {
		cout << "������׷��� 2���� �����Ͱ� �ƴԴϴ�." << endl;
		exit(1);
	}
	float ratio_value = 512;
	float ratio_hue   = 180.f / hist.rows;			// ���� ������ ����
	float ratio_sat   = 256.f / hist.cols;			// ä�� ������ ����

	Mat graph(hist.size(), CV_32FC3);
	for (int i = 0; i < hist.rows; i++) {
		for (int j = 0; j < hist.cols; j++)
		{
			float value = hist.at<float>(i, j) * ratio_value ;
			float hue   = i * ratio_hue;
			float sat   = j * ratio_sat;
			graph.at<Vec3f>(i, j) = Vec3f(hue, sat, value);
		}
	}

	graph.convertTo(graph, CV_8U);
	cvtColor(graph, graph, CV_HSV2BGR);
	resize(graph, graph, Size(0, 0), 10, 10, INTER_NEAREST);

	return graph;
}

int main()
{
	Vec3i bins(30, 42, 0);
	Vec3f ranges(180, 256, 0);
	
	int q_no = 66;
	String  fname = format("../image/DB/img_%02d.jpg", q_no);
	Mat image = imread(fname, IMREAD_COLOR);
	CV_Assert(image.data);

	Mat hsv, hist;
	cvtColor(image, hsv, CV_BGR2HSV);			// HSV �÷� ��ȯ
	calc_Histo(hsv, hist, bins, ranges, 2);			// 2���� ������׷� ���
	Mat hist_img = draw_histo(hist); 				// 2���� �׷��� ����

	imshow("image", image);
	imshow("hist_img", hist_img);
	waitKey();
	return 0;
}