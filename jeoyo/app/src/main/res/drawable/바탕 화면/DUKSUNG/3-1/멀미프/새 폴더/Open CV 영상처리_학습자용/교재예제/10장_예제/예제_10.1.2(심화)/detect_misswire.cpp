#include "utils4.hpp"

void main()
{
	//---------------------------------------------
	// 변수 설정
	float  scale = 0.3f;																// 영상 축소 비율
	vector<Rect>  rect;
	Mat		gray, resize_gray,  canny , morph , mo_flip ;

	//---------------------------------------------------------------------------
	// 영상 입력
	//---------------------------------------------------------------------------
	Mat src = readImage( "chap6/4/0.tif" );						// 영상 읽기
	
	//---------------------------------------------------------------------------
	// 하네스 영상 추출 
	//---------------------------------------------------------------------------
	cvtColor( src , gray, CV_BGR2GRAY );							// 명암도 영상 변환
	resize ( gray , resize_gray , Size() , scale, scale );				// 영상 축소
	Canny ( resize_gray , canny , 40 , 100 );							// 에지 검출(Canny)
	
	// 모폴로지 팽장 2번 수행
	morphologyEx( canny , morph ,MORPH_DILATE , Mat() , Point(-1, -1) , 2 ); 

	//---------------------------------------------
	// 레이블링 수행 - (mode=0) 가장 큰 객체 영역 가져옴
	labeling( morph , rect, 0 );							

	//---------------------------------------------
	// 검출 하네스 사각형 원본 크기 복원 
	int re_x = cvRound(rect[0].x / scale) ; 
	int re_y = cvRound(rect[0].y / scale) ; 
	int re_w = cvRound(rect[0].width / scale) ; 
	int re_h = cvRound(rect[0].height / scale) ; 

	//---------------------------------------------
	// 하네스 영상 
	Rect	harness_rect ( re_x, re_y, re_w ,re_h);			// 하네스 사각형 
	Mat	harness_object = gray( harness_rect )	;			// 영상 가져옴

	//---------------------------------------------
	// 중간 수행영상 보기
	//imshow("캐니에지", canny);
	//imshow("팽창연산", morph);
	//rectangle ( morph , rect[0] , Scalar(255) ,1)  ;
	//imshow("라벨링:", morph);
	//imshow("하네스영상:", harness_object);

	//---------------------------------------------------------------------------
	// 와이어 검사 영역 추출
	//---------------------------------------------------------------------------
	// 객체 왼쪽 3분의 1 
	Rect sub_roi ( 0, 0 , harness_object.cols/3, harness_object.rows) ;			
	Mat  sub_object = harness_object(sub_roi).clone();
	
	//---------------------------------------------
	//// 이진화 및 팽창 연산
	threshold( sub_object , sub_object , 250 , 255 , CV_THRESH_BINARY );   //이진 영상 변환
	morphologyEx( sub_object , morph , CV_MOP_DILATE , Mat() , Point(-1 , -1) , 4);

	//---------------------------------------------
	// 컨텍터 위치 검출
	int x1 ,y0 , y1 ;
	flip(morph, mo_flip , 1);									// 오른쪽 끝 찾기 위해 영상 좌우 반전

	find_histo( morph	, x1 , VERTICAL ) ;			// 수직 투영에서 커넥터 위치 찾기
	find_histo( morph	, y0 , HORIZONTAL ) ;		// 수평 투영에서 커넥터 왼쪽 위치 찾기
	find_histo( mo_flip	, y1 , HORIZONTAL ) ;	// 수평 투영에서 커넥터 오른쪽 위치 찾기
	y1 = (morph.cols - y1) ;					// 오른쪽 위치

	//---------------------------------------------
	// 커넥터의 오른쪽 상단 좌표
	int test_region_width = 25 , margin = 15 ; 
	Point	conector_tr(x1 + margin , y0) ;

	//---------------------------------------------
	// 와이어 검사 영상 추출
	Rect	test_roi( conector_tr , Size(test_region_width, y1)  ) ;
	Mat	test_region  	    = src (test_roi + harness_rect.tl()).clone();	 	// 와이어 영역 추출
	Mat	test_region_gray 	= gray(test_roi + harness_rect.tl()).clone();	// 명암도 영상

	//----------------------------------------------------------------------
	// 개별 와이어 영상 추출
	//----------------------------------------------------------------------
	vector<Rect> wire_roi = extract_wires( test_region_gray );				// 개별 와이어 영역 사각형
	
	//---------------------------------------------
	// 개별 와이어 영상 
	vector<Mat> wires ;
	for( int i = 0; i< (int) wire_roi.size(); i++ ) {
		wires.push_back( test_region( wire_roi[i] ) );									// 각 와이어 영역 추출
	}

	//----------------------------------------------------------------------
	// 개별 와이어 영상의 상관도 계산
	//----------------------------------------------------------------------
	Mat		correlation = mat_mahalanobis ( wires ) ;				// 마할노비니스 거리 상관도 계산

	//----------------------------------------------------------------------
	// 상관도에 의한 불량 판별
	//----------------------------------------------------------------------
	Point	text_pt(100, 100);
	bool	check	= ischeck( correlation) ;									// 불량 검사
	if ( check ) {
		putText ( src, "GOOD", text_pt , FONT_HERSHEY_PLAIN,6 , CV_RGB(0 ,255, 0) , 3 );
	} 
	else {
		putText ( src, "NG" , text_pt, FONT_HERSHEY_PLAIN , 6 , CV_RGB(255, 0, 0) , 3 );
	}

	//---------------------------------------------
	// 영상 표시
	imshow( "display" ,  src );
//	imshow("1/3 영상:", sub_object);
//	imshow("팽창연산2", morph);
//	imshow("와이어검사영상1", test_region_gray);
//	imshow("와이어검사영상2", test_region);
	waitKey(0);
}
