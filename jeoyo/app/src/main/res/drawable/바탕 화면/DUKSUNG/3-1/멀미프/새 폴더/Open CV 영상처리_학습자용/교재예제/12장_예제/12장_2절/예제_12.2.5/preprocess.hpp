#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat  preprocessing(Mat image)
{
	Mat gray, th_img, morph;
	Mat kernel(5, 25, CV_8UC1, Scalar(1));		// 닫힘 연산 마스크
	cvtColor(image, gray, CV_BGR2GRAY);		// 명암도 영상 변환

	blur(gray, gray, Size(5, 5));				// 블러링
	Sobel(gray, gray, CV_8U, 1, 0, 3);			// 소벨 에지 검출

	threshold(gray, th_img, 120, 255, THRESH_BINARY);	// 이진화 수행
	morphologyEx(th_img, morph, MORPH_CLOSE, kernel);													//	morphologyEx(th_img, morph, MORPH_CLOSE, kernel);	// 열림 연산 수행	
	//	imshow("th_img", th_img), imshow("morph", morph);
	return morph;
}

bool vertify_plate(RotatedRect mr)
{
	float size = mr.size.area();
	float aspect = (float)mr.size.height / mr.size.width;	// 종횡비 계산
	if (aspect < 1)  aspect = 1 / aspect;

	bool  ch1 = size > 2000 && size < 30000;		// 번호판 넓이 조건
	bool  ch2 = aspect > 1.3 && aspect < 6.4;		// 번호판 종횡비 조건

	return  ch1 && ch2;
}

void find_candidates(Mat img, vector<RotatedRect>& candidates)
{
	vector< vector< Point> > contours;				// 외곽선
													// 외곽선 검출
	findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	for (int i = 0; i< (int)contours.size(); i++)	// 검출 외곽선 조회
	{
		RotatedRect  rot_rect = minAreaRect(contours[i]);	// 외곽선 최소영역 회전사각형
		if (vertify_plate(rot_rect))						// 번호판 검증
			candidates.push_back(rot_rect);				// 회전사각형 저장
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
