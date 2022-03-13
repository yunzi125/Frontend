void  refine_candidate(Mat image, RotatedRect& candi)
{
	Mat fill(image.size() + Size(2, 2), CV_8UC1, Scalar(0));   	// 채움 영역
	Scalar  dif1(25, 25, 25), dif2(25, 25, 25);						// 채움 색상 범위 
	int  flags = 4 + 0xff00;										// 채움 방향
	flags += FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;

	// 후보영역 유사 컬러 채움
	vector<Point2f> rand_pt(15);						// 랜덤 좌표 15개
	randn(rand_pt, 0, 7);
	Rect img_rect(Point(0, 0), image.size());			// 입력영상 범위 사각형
	for (int i = 0; i < rand_pt.size(); i++) {
		Point2f seed = candi.center + rand_pt[i];		// 랜덤좌표 평행이동
		if (img_rect.contains(seed)) {					// 입력영상 범위이면
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
	candi = minAreaRect(fill_pts);				// 채움 좌표들로 최소영역 계산
}

void  rotate_plate(Mat image, Mat& corp_img, RotatedRect candi)
{
	float aspect = (float)candi.size.width / candi.size.height;	// 종횡비 
	float angle = candi.angle;									// 회전각도	

	if (aspect < 1) {											// 1보다 작으면 세로로 긴 영역
		swap(candi.size.width, candi.size.height);				// 가로 세로 맞바꿈
		angle += 90;											// 회전각도 조정
	}

	Mat rotmat = getRotationMatrix2D(candi.center, angle, 1);			// 회전 행렬 계산
	warpAffine(image, corp_img, rotmat, image.size(), INTER_CUBIC);	// 회전변환 수행
	getRectSubPix(corp_img, candi.size, candi.center, corp_img);
}

vector<Mat> make_candidates(Mat image, vector<RotatedRect>& candidates)
{
	vector<Mat> candidates_img;
	for (int i = 0; i < (int)candidates.size();)
	{
		refine_candidate(image, candidates[i]);		// 후보 영역 개선
		if (vertify_plate(candidates[i]))				// 개선 영역 재검증
		{
			Mat corp_img;
			rotate_plate(image, corp_img, candidates[i]);	// 회전 및 후보영상 가져오기

			cvtColor(corp_img, corp_img, CV_BGR2GRAY); 				// 명암도 변환
			resize(corp_img, corp_img, Size(144, 28), 0, 0, INTER_CUBIC); // 크기 정규화
			candidates_img.push_back(corp_img);						// 보정 영상 저장
			i++;
		}
		else 											// 재검증 탈락 
			candidates.erase(candidates.begin() + i);	// 벡터 원소에서 제거

	}
	return candidates_img;
}
