void  refine_candidate(Mat image, RotatedRect& candi)
{
	Mat fill(image.size() + Size(2, 2), CV_8UC1, Scalar(0));   	// ä�� ����
	Scalar  dif1(25, 25, 25), dif2(25, 25, 25);						// ä�� ���� ���� 
	int  flags = 4 + 0xff00;										// ä�� ����
	flags += FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;

	// �ĺ����� ���� �÷� ä��
	vector<Point2f> rand_pt(15);						// ���� ��ǥ 15��
	randn(rand_pt, 0, 7);
	Rect img_rect(Point(0, 0), image.size());			// �Է¿��� ���� �簢��
	for (int i = 0; i < rand_pt.size(); i++) {
		Point2f seed = candi.center + rand_pt[i];		// ������ǥ �����̵�
		if (img_rect.contains(seed)) {					// �Է¿��� �����̸�
			floodFill(image, fill, seed, Scalar(), &Rect(), dif1, dif2, flags);
		}
	}

	// ä�� ���� �簢�� ���
	vector<Point> fill_pts;
	for (int i = 0; i < fill.rows; i++) {			// ä�� ��� ���� ��ȸ
		for (int j = 0; j < fill.cols; j++) {
			if (fill.at<uchar>(i, j) == 255) 		// ä�� �����̸� 
				fill_pts.push_back(Point(j, i));		// ��ǥ ����
		}
	}
	candi = minAreaRect(fill_pts);				// ä�� ��ǥ��� �ּҿ��� ���
}

void  rotate_plate(Mat image, Mat& corp_img, RotatedRect candi)
{
	float aspect = (float)candi.size.width / candi.size.height;	// ��Ⱦ�� 
	float angle = candi.angle;									// ȸ������	

	if (aspect < 1) {											// 1���� ������ ���η� �� ����
		swap(candi.size.width, candi.size.height);				// ���� ���� �¹ٲ�
		angle += 90;											// ȸ������ ����
	}

	Mat rotmat = getRotationMatrix2D(candi.center, angle, 1);			// ȸ�� ��� ���
	warpAffine(image, corp_img, rotmat, image.size(), INTER_CUBIC);	// ȸ����ȯ ����
	getRectSubPix(corp_img, candi.size, candi.center, corp_img);
}

vector<Mat> make_candidates(Mat image, vector<RotatedRect>& candidates)
{
	vector<Mat> candidates_img;
	for (int i = 0; i < (int)candidates.size();)
	{
		refine_candidate(image, candidates[i]);		// �ĺ� ���� ����
		if (vertify_plate(candidates[i]))				// ���� ���� �����
		{
			Mat corp_img;
			rotate_plate(image, corp_img, candidates[i]);	// ȸ�� �� �ĺ����� ��������

			cvtColor(corp_img, corp_img, CV_BGR2GRAY); 				// ��ϵ� ��ȯ
			resize(corp_img, corp_img, Size(144, 28), 0, 0, INTER_CUBIC); // ũ�� ����ȭ
			candidates_img.push_back(corp_img);						// ���� ���� ����
			i++;
		}
		else 											// ����� Ż�� 
			candidates.erase(candidates.begin() + i);	// ���� ���ҿ��� ����

	}
	return candidates_img;
}
