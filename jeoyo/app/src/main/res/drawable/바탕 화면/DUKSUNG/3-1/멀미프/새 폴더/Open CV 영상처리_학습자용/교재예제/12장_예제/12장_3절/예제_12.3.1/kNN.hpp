void find_histoPos(Mat img, int & start, int &end, int direct)
{
	reduce(img, img, direct, REDUCE_AVG);

	int  minFound = 0;
	for (int i = 0; i< (int)img.total(); i++) {
		if (img.at<uchar>(i) < 250) 		// ������� �ƴϸ�
		{
			end = i;						// ������׷� ������ ��ġ
			if (!minFound) {
				start = i;					// ������׷� ù ��ġ
				minFound = 1;
			}
		}
	}
}

Mat find_number(Mat part)
{
	Point start, end;
	find_histoPos(part, start.x, end.x, 0);		// ���� ���� 
	find_histoPos(part, start.y, end.y, 1);   	// ���� ���� 

	return part(Rect(start, end));				// ���ڰ�ü ����
}

Mat  place_middle(Mat number, Size new_size)
{
	int  big = max(number.cols, number.rows);
	Mat  square(big, big, number.type(), Scalar(255));	// ���濵��

	Point start = (square.size() - number.size()) / 2;

	Rect middle_rect(start, number.size());			// �߽� �簢��
	Mat middle = square(middle_rect);
	number.copyTo(middle);

	resize(square, square, new_size);				// ũ�� ����
	square.convertTo(square, CV_32F);

	return square.reshape(0, 1);
}


Ptr<ml::KNearest>   kNN_train(string train_img, int K, int Nclass, int Nsample)
{
	Size  size(40, 40);									// �� ũ��
	Mat  trainData, classLable;
	Mat  train_image = imread(train_img, 0);			// ��ü �н����� �ε�
	CV_Assert(train_image.data);

	threshold(train_image, train_image, 32, 255, THRESH_BINARY);
	for (int i = 0, k = 0; i<Nclass; i++) {
		for (int j = 0; j< Nsample; j++, k++)
		{
			Point pt(j * size.width, i * size.height);		// �� ������ǥ
			Rect  roi(pt, size);
			Mat   part = train_image(roi);					// ���� ���� �и�

			Mat  num = find_number(part);			// ���ڰ�ü ����
			Mat  data = place_middle(num, size);			// �� �߽ɿ� ���� ��ġ 
			trainData.push_back(data);						// �н� ������ ����
			classLable.push_back(i);						// ���̺�
		}
	}

	Ptr<ml::KNearest>  knn = ml::KNearest::create();			// k-NN ��ü ����
	knn->train(trainData, ml::ROW_SAMPLE, classLable);		// k-NN �н�
	return knn;
}