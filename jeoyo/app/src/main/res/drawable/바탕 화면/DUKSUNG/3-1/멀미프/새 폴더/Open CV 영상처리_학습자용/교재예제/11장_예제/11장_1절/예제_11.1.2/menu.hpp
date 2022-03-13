int   hue; 										// hue 값 - 전역변수 지정

void place_icons(Size size)						// size : 아이콘 크기
{
	vector<string> icon_name = {				// 아이콘 파일 이름
		"rect", "circle", "eclipe", "line", "brush", "eraser",
		"open", "save", "plus", "minus" ,"clear",  "color"
	};

	int btn_rows = (int)cvCeil(icon_name.size() / 2.0);			// 2열 버튼의 행수

	for (int i = 0, k = 0; i < btn_rows; i++) {
		for (int j = 0; j < 2; j++, k++)
		{
			Point   pt(j*size.width, i*size.height);			// 각 아이콘 시작위치 
			icons.push_back(Rect(pt, size));					// 각 아이콘 관심영역

			Mat icon = imread("../image/icon/" + icon_name[k] + ".jpg", 1);
			if (icon.empty()) continue; 					// 예외처리

			resize(icon, icon, size);					// 아이콘 영상 크기 통일
			icon.copyTo(image(icons[k]));					// 아이콘 영상 복사
		}
	}
}

void  create_hueIndex(Rect rect)				 // rect - 색상인덱스 영역
{
	Mat  m_hueIdx = image(rect);					// 색상인덱스 영역 참조
	float  ratio = 180.0f / rect.height;				// 색상인덱스 세로크기의 hue 스케일

	for (int i = 0; i < rect.height; i++)
	{
		Scalar  hue_color(i*ratio, 255, 255);		// HSV 색상 지정	
		m_hueIdx.row(i).setTo(hue_color);			// 한 행의 색상 지정
	}
	cvtColor(m_hueIdx, m_hueIdx, CV_HSV2BGR);		// HSV에서 RGB로 변환
}

// pos_y : 마우스 클릭 y 좌표, rect_pale: 팔레트 영역
void  create_palette(int pos_y, Rect rect_pale)
{
	Mat		m_palatte = image(rect_pale);				// 팔레트 영역 참조
	float  	ratio1 = 180.0f / rect_pale.height;			// 팔레트 높이에 따른 hue 비율
	float  	ratio2 = 256.0f / rect_pale.width;			// 팔레트 너비에 따른 saturation 비율 
	float  	ratio3 = 256.0f / rect_pale.height;			// 팔레트 높이에 따른 intensity 비율

	hue = cvRound((pos_y - rect_pale.y) * ratio1);		// 색상팔레트 기본 색상

	for (int i = 0; i < m_palatte.rows; i++) {				// 색상팔레트 조회
		for (int j = 0; j < m_palatte.cols; j++)
		{
			int saturation = cvRound(j * ratio2);							// 채도 계산
			int intensity = cvRound((m_palatte.rows - i - 1) * ratio3);	// 명도 계산
			m_palatte.at<Vec3b>(i, j) = Vec3b(hue, saturation, intensity);	// HSV 색상 지정
		}
	}
	cvtColor(m_palatte, m_palatte, CV_HSV2BGR);		// HSV에서 RGB로 변환
}