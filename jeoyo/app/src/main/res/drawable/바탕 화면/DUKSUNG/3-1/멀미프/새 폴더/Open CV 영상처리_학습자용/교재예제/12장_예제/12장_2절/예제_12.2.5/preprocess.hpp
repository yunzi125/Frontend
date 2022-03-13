#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat  preprocessing(Mat image)
{
	Mat gray, th_img, morph;
	Mat kernel(5, 25, CV_8UC1, Scalar(1));		// ���� ���� ����ũ
	cvtColor(image, gray, CV_BGR2GRAY);		// ��ϵ� ���� ��ȯ

	blur(gray, gray, Size(5, 5));				// ����
	Sobel(gray, gray, CV_8U, 1, 0, 3);			// �Һ� ���� ����

	threshold(gray, th_img, 120, 255, THRESH_BINARY);	// ����ȭ ����
	morphologyEx(th_img, morph, MORPH_CLOSE, kernel);													//	morphologyEx(th_img, morph, MORPH_CLOSE, kernel);	// ���� ���� ����	
	//	imshow("th_img", th_img), imshow("morph", morph);
	return morph;
}

bool vertify_plate(RotatedRect mr)
{
	float size = mr.size.area();
	float aspect = (float)mr.size.height / mr.size.width;	// ��Ⱦ�� ���
	if (aspect < 1)  aspect = 1 / aspect;

	bool  ch1 = size > 2000 && size < 30000;		// ��ȣ�� ���� ����
	bool  ch2 = aspect > 1.3 && aspect < 6.4;		// ��ȣ�� ��Ⱦ�� ����

	return  ch1 && ch2;
}

void find_candidates(Mat img, vector<RotatedRect>& candidates)
{
	vector< vector< Point> > contours;				// �ܰ���
													// �ܰ��� ����
	findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (int i = 0; i< (int)contours.size(); i++)	// ���� �ܰ��� ��ȸ
	{
		RotatedRect  rot_rect = minAreaRect(contours[i]);	// �ܰ��� �ּҿ��� ȸ���簢��
		if (vertify_plate(rot_rect))						// ��ȣ�� ����
			candidates.push_back(rot_rect);				// ȸ���簢�� ����
	}
}

void draw_rotatedRect(Mat &img, RotatedRect mr, Scalar color, int thickness = 2)
{
	Point2f  pts[4];
	mr.points(pts);

	for (int i = 0; i <4; ++i) {
		line(img, pts[i], pts[(i + 1) % 4], color, thickness);
	}
}
