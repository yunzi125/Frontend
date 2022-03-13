void replace_icon(Size b_size)
{
	vector<string> btn_icon = {				// ������ ���� �̸�
		"rect", "circle", "eclipe", "line", "brush", "eraser",
		"open", "save", "plus", "minus" , "clear", "color"
	};

	int btn_rows = (int)cvCeil(btn_icon.size() / 2.0);			// 2�� ��ư�� ���

	for (int i = 0, k = 0; i < btn_rows; i++) {
		for (int j = 0; j < 2; j++, k++)
		{
			Point   pt(j*b_size.width, i*b_size.height);			// �� ������ ������ġ 
			btn.push_back(Rect(pt, b_size));					// �� ������ ���ɿ���

			Mat icon = imread("../image/icon/" + btn_icon[k] + ".jpg", 1);
			if (icon.empty()) continue; 					// ����ó��

			resize(icon, icon, b_size);					// ������ ���� ũ�� ����
			icon.copyTo(image(btn[k]));					// ������ ���� ����
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
	float  ratio1 = 180.0f / pal_rect.height;		// hue ���� ������
	float  ratio2 = 256.0f / pal_rect.width;			// saturation ���� ������ 
	float  ratio3 = 256.0f / pal_rect.height;		// intensity ���� ������

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
