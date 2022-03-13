#include "hough.hpp"

void max_object(Mat img, Rect &rect ) 
{
	vector<vector<Point>> contours;
	findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);	// 외곽선 검출
	
	int max_area = 0 ;
	for (int i = 0; i < (int)contours.size(); i++)	// 가장 큰 영역 가져오기
	{
		Rect r = boundingRect(contours[i]);			// 외곽선 영역 포함 사각형
		if (max_area < r.area()) {
			max_area = r.area();
			rect = r;
		}
	}
	rect = rect - Point(10, 10) + Size(20, 20);
}

void main()
{
	Rect  rect;
	Mat		gray, canny, morph, th_gray, canny_line, dst;
	double rho = 1, theta = CV_PI / 180;				// 허프변환 거리간격, 각도간격
	vector<Vec2f> lines;								// 허프 검출 라인들

	Mat  image = imread("../image/5.tif" , 1);
	CV_Assert(image.data);

	cvtColor(image, gray, CV_BGR2GRAY);						// 명암도 영상 변환
	threshold(gray, th_gray, 240, 255, THRESH_BINARY);		//이진 영상 변환
	erode(th_gray, morph, Mat(), Point(-1, -1), 2);			// 침식 연산

	max_object(morph, rect);								// 가장 큰 객체 검색
	rectangle(morph, rect, Scalar(100), 2);					// 검색 객체 표시

	Canny(th_gray(rect), canny, 40, 100);
	houghLines(canny, lines, rho, theta, 50);
	draw_houghLines(canny, canny_line, lines, 1);

	double angle = (CV_PI - lines[0][1]) * 180 / CV_PI  ;
	Point  center = image.size() / 2;
	Mat rot_map = getRotationMatrix2D(center, -angle, 1);
	
	warpAffine(image, dst, rot_map, image.size(), INTER_LINEAR);
	imshow("morph", morph);
	imshow("image", image);
	imshow("line", canny_line);
	imshow("dst", dst);

	resizeWindow("line", 150, 150);
	waitKey();
}

//resize(gray, resize_gray, Size(), scale, scale);			// 영상 축소
//Canny(resize_gray, canny, 40, 100);						// 케니 에지 검출
//dilate(canny, morph, Mat(), Point(-1, -1), 2);			// 팽창 연산 2번 수행

//max_object(morph, rect);									// 가장 큰 객체 추출

//// 검출 하네스 사각형 원본 크기 복원 
//Point pt1 = rect.tl() / scale;
//Point pt2 = rect.br() / scale;
//Rect	harness_rect(pt1, pt2);					// 하네스 사각형 
//Mat	harness_object = gray(harness_rect);	// 영상 가져옴