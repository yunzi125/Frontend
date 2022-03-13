void replace_icon(Size b_size)
{
	vector<string> btn_icon = {				// 아이콘 파일 이름
		"rect", "circle", "eclipe", "line", "brush", "eraser",
		"open", "save", "plus", "minus" , "clear", "color"
	};

	int btn_rows = (int)cvCeil(btn_icon.size() / 2.0);			// 2열 버튼의 행수

	for (int i = 0, k = 0; i < btn_rows; i++) {
		for (int j = 0; j < 2; j++, k++)
		{
			Point   pt(j*b_size.width, i*b_size.height);			// 각 아이콘 시작위치 
			btn.push_back(Rect(pt, b_size));					// 각 아이콘 관심영역

			Mat icon = imread("../image/icon/" + btn_icon[k] + ".jpg", 1);
			if (icon.empty()) continue; 					// 예외처리

			resize(icon, icon, b_size);					// 아이콘 영상 크기 통일
			icon.copyTo(image(btn[k]));					// 아이콘 영상 복사
		}
	}
}

void  pallette_index(Rect pal_idx)
{
	Mat  p_index = image(pal_idx);
	float  ratio = 180.0f / pal_idx.height;

	for (int i = 0; i < p_index.rows; i++)
	{
		Scalar  hue_color(i*ratio, 255, 255);
		p_index.row(i).setTo(hue_color);
	}
	cvtColor(p_index, p_index, CV_HSV2BGR);
}

void  make_palette(int pos_y, Rect pal_rect)
{
	Mat    palatte = image(pal_rect);
	float  ratio1 = 180.0f / pal_rect.height;		// hue 범위 스케일
	float  ratio2 = 256.0f / pal_rect.width;			// saturation 범위 스케일 
	float  ratio3 = 256.0f / pal_rect.height;		// intensity 범위 스케일

	hue = cvRound((pos_y - pal_rect.y) * ratio1);

	for (int i = 0; i < palatte.rows; i++) {
		for (int j = 0; j < palatte.cols; j++)
		{
			int saturation = cvRound(j * ratio2);
			int intensity = cvRound((palatte.rows - i - 1) * ratio3);

			palatte.at<Vec3b>(i, j) = Vec3b(hue, saturation, intensity);
		}
	}
	cvtColor(palatte, palatte, CV_HSV2BGR);
}
