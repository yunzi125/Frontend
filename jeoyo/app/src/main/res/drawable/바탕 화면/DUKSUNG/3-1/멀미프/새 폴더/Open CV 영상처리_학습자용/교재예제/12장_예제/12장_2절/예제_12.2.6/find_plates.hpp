void  read_trainData(string fn, Mat & trainingData, Mat & classes = Mat())
{
	FileStorage fs(fn, FileStorage::READ);
	CV_Assert(fs.isOpened());

	fs["TrainingData"] >> trainingData;
	fs["classes"] >> classes;
	fs.release();

	trainingData.convertTo(trainingData, CV_32FC1);
}

Mat  preprocessing(Mat image, Mat& morph)
{
	Mat gray, sobel, th_img;
	Mat kernel(5, 25, CV_8UC1, Scalar(1));
	cvtColor(image, gray, CV_BGR2GRAY);		// 명암도 영상 변환
	blur(gray, gray, Size(5, 5));				// 블러링
	Sobel(gray, gray, CV_8U, 1, 0, 3);			// 소벨 에지 검출

	threshold(gray, th_img, 120, 255, THRESH_BINARY);	// 이진화 수행
	morphologyEx(th_img, morph, MORPH_CLOSE, kernel);	// 열림 연산 수행
	//	imshow("th_img", th_img), imshow("morph", morph);
	return morph;
}

bool vertify_plate(RotatedRect mr)
{
	float size = mr.size.area();
	float aspect = (float)mr.size.width / mr.size.height;

	if (aspect < 1) aspect = 1 / aspect;

	bool  ch1 = size > 1000 && size < 50000;
	bool  ch2 = aspect > 1.3 && aspect < 6.4;

	return  ch1 && ch2;
}

void find_candidates(Mat img, vector<RotatedRect>& candidates)
{
	vector< vector< Point> > contours;				// 외곽선
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

//void  refine_plate(Mat image, RotatedRect& rect)
//{
//	srand((int)time(NULL));
//	int radius = min(rect.size.width, rect.size.height) * 0.30;
//
//	Scalar  dif1(25, 25, 25), dif2(25, 25, 25);
//	int  connect = 4 + 0xff00;
//	int  flags = connect + FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;
//
//	Mat mask(image.size() + Size(2, 2), CV_8UC1, Scalar(0));
//
//	for (int j = 0; j < 10; j++)
//	{
//		int rand_radius = rand() % radius - (radius / 2);
//		Point2f seed = rect.center + Point2f(rand_radius, rand_radius);
//		int area = floodFill(image, mask, seed, Scalar(), &Rect(), dif1, dif2, flags);
//	}
//
//	vector<Point> mask_pt;
//	for (int i = 0; i < mask.rows; i++) {
//		for (int j = 0; j < mask.cols; j++)
//		{
//			if (mask.at<uchar>(i, j) == 255) mask_pt.push_back(Point(j, i));
//		}
//	}
//
//	rect = minAreaRect(mask_pt);
//}

void  refine_candidate(Mat image, RotatedRect& candidate)
{
	Mat fill(image.size() + Size(2, 2), CV_8UC1, Scalar(0));   	// 채움 영역
	Scalar  dif1(25, 25, 25), dif2(25, 25, 25);						// 채움 색상 범위 
	int  flags = 4 + 0xff00;										// 채움 방향
	flags += FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;

	// 후보영역 유사 컬러 채움
	vector<Point2f> rand_pt(10);
	randn(rand_pt, 0, 7);								// 랜덤 좌표 10개 생성
	Rect img_rect(Point(0, 0), image.size());			// 입력영상 범위 사각형
	for (int i = 0; i < 10; i++) {
		Point2f seed = candidate.center + rand_pt[i];	// 후보영역 중심으로 랜덤좌표 이동
		if (img_rect.contains(seed)) {					// 랜덤좌표가 입력영상 범위이면
			floodFill(image, fill, seed, Scalar(), &Rect(), dif1, dif2, flags);
		}
	}

	// 채움 영역 사각형 계산
	vector<Point> fill_pts;
	for (int i = 0; i < fill.rows; i++) {			// 채움 행렬 원소 조회
		for (int j = 0; j < fill.cols; j++) {
			if (fill.at<uchar>(i, j) == 255) 		// 채움 영역이면 
				fill_pts.push_back(Point(j, i));		// 좌표 저장
		}
	}
	candidate = minAreaRect(fill_pts);				// 채움 좌표들로 최소영역 계산
}


Mat  correct_plate(Mat input, RotatedRect ro_rect)
{
	Size  m_size = ro_rect.size;
	float aspect = (float)m_size.width / m_size.height;
	float angle = ro_rect.angle;

	if (aspect < 1) {
		angle += 90;
		swap(m_size.width, m_size.height);
	}

	Mat rot_img, correct_img;
	Mat rotmat = getRotationMatrix2D(ro_rect.center, angle, 1);
	warpAffine(input, rot_img, rotmat, input.size(), CV_INTER_CUBIC);

	getRectSubPix(rot_img, m_size, ro_rect.center, correct_img);
	resize(correct_img, correct_img, Size(144, 28), 0, 0, INTER_CUBIC);

	return correct_img;
}


Ptr<ml::SVM> SVM_train(string fn)
{
	Mat	 trainingData, labels;
	read_trainData(fn, trainingData, labels);

	Ptr<ml::SVM> svm = ml::SVM::create();
	svm->setType(ml::SVM::C_SVC);
	svm->setKernel(ml::SVM::LINEAR);
	svm->setGamma(1);
	svm->setC(1);
	svm->setTermCriteria(TermCriteria(CV_TERMCRIT_ITER, 1000, 0.01));
	svm->train(trainingData, ml::ROW_SAMPLE, labels);

	return svm;
}

vector<Mat> make_candidates(Mat img, vector<RotatedRect>& ro_rects)
{
	vector<Mat> candidates;
	for (size_t i = 0; i < ro_rects.size();) {
		refine_candidate(img, ro_rects[i]);		// 후보 영역 개선

		if (vertify_plate(ro_rects[i]))
		{
			Mat corr_img = correct_plate(img, ro_rects[i]);
			cvtColor(corr_img, corr_img, CV_BGR2GRAY);
			candidates.push_back(corr_img);						// 보정 영상 저장

			imshow("plate_img - " + to_string(i), corr_img);
			resizeWindow("plate_img - " + to_string(i), 200, 50);	//윈도우 크기 조정
			i++;
		}
		else 	ro_rects.erase(ro_rects.begin() + i);

	}
	return candidates;
}

int classify_plates(Ptr<ml::SVM> svm, vector<Mat> candidate_img)
{
	for (int i = 0; i < (int)candidate_img.size(); i++)
	{
		Mat onerow = candidate_img[i].reshape(1, 1);
		onerow.convertTo(onerow, CV_32F);

		Mat results;
		svm->predict(onerow, results);

		if (results.at<float>(0) == 1)
			return i;
	}
	return -1;
}