void classify(Mat& image, Mat hists[4], int no)
{
	double criteria1 = compareHist(hists[0], hists[1], CV_COMP_CORREL);
	double criteria2 = compareHist(hists[2], hists[3], CV_COMP_CORREL);
	
	double tmp = (criteria1 > 0.2) ? 0.2 : 0.4;
	int value = (criteria2 > tmp) ? 0 : 1;

	string text = (value) ? "Man" : "Woman";
	text = format("%02d.jpg: ", no) + text;

	int font = FONT_HERSHEY_TRIPLEX;
	putText(image, text, Point(12, 31), font, 0.7, Scalar(0, 0, 0), 2);
	putText(image, text, Point(10, 30), font, 0.7, Scalar(0, 255, 0), 1);

	cout << text << format(" - 유사도 [머리: %4.2f  입술: %4.2f]\n", criteria1, criteria2);
}

void display(Mat &image, Point2d face_center, vector<Point2f> eyes_center, vector<Rect> sub)
{
	circle(image, eyes_center[0], 10, Scalar(0, 255, 0), 2);			// 눈 표시
	circle(image, eyes_center[1], 10, Scalar(0, 255, 0), 2);
	circle(image, face_center, 3, Scalar(0, 0, 255), 2);			// 얼굴 중심점 표시

	draw_ellipse(image, sub[2], Scalar(255, 100, 0), 2, 0.45f);	// 입술 타원	
	draw_ellipse(image, sub[3], Scalar(0, 0, 255), 2, 0.45f);	// 얼굴 타원	
}