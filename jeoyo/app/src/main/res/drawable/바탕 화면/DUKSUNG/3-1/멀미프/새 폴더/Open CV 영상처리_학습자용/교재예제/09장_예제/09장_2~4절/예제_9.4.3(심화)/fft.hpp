Mat  zeropadding(Mat img)
{
	int  m = 1 << (int)ceil(log2(img.rows));		// 2의 자승 계산
	int  n = 1 << (int)ceil(log2(img.cols));
	Mat dst(m, n, img.type(), Scalar(0));

	Rect rect(Point(0, 0), img.size());				// 원본 영상크기 관심영역
	img.copyTo(dst(rect));							// 원본영상을 관심영역에 복사
	dst.convertTo(dst, CV_32F);
	return dst;
}

void log_mag(Mat complex_mat, Mat& dst)
{
	Mat  planes[2];
	split(complex_mat, planes);
	magnitude(planes[0], planes[1], dst);
	log(dst + 1, dst);
	normalize(dst, dst, 0, 255, CV_MINMAX);
	dst.convertTo(dst, CV_8U);
}

void shuffling(Mat mag_img, Mat& dst)
{
	int  cx = mag_img.cols / 2;
	int  cy = mag_img.rows / 2;
	Rect q1(cx, 0, cx, cy);		// 1사분면 사각형
	Rect q2(0, 0, cx, cy);		// 2사분면 사각형
	Rect q3(0, cy, cx, cy);		// 3사분면 사각형
	Rect q4(cx, cy, cx, cy);		// 4사분면 사각형

	dst = Mat(mag_img.size(), mag_img.type());
	mag_img(q1).copyTo(dst(q3));
	mag_img(q3).copyTo(dst(q1));
	mag_img(q2).copyTo(dst(q4));
	mag_img(q4).copyTo(dst(q2));
}

void FFT(Mat image, Mat& dft_coef, Mat& spectrum_img)		// fft 전체 과정 수행
{
	Mat complex_mat;
	Mat pad_img = zeropadding(image);
	Mat  tmp[] = { pad_img, Mat::zeros(pad_img.size(), pad_img.type()) };
	merge(tmp, 2, complex_mat);
	dft(complex_mat, dft_coef, 0);
	shuffling(dft_coef, dft_coef);
	log_mag(dft_coef, spectrum_img);
}

Mat IFFT(Mat dft_coef, Size size)								// ifft 전체 과정 수행
{
	Mat idft_coef, idft_img[2];
	shuffling(dft_coef, dft_coef);
	dft(dft_coef, idft_coef, DFT_INVERSE + DFT_SCALE);
	split(idft_coef, idft_img);

	Rect img_rect(Point(0, 0), size);
	idft_img[0](img_rect).convertTo(idft_img[0], CV_8U);		// 입력 영상 크기에 맞춰 복사
	return idft_img[0];
}
