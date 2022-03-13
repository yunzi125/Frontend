#include "utils4.hpp"

void main()
{
	//---------------------------------------------
	// ���� ����
	float  scale = 0.3f;																// ���� ��� ����
	vector<Rect>  rect;
	Mat		gray, resize_gray,  canny , morph , mo_flip ;

	//---------------------------------------------------------------------------
	// ���� �Է�
	//---------------------------------------------------------------------------
	Mat src = readImage( "chap6/4/0.tif" );						// ���� �б�
	
	//---------------------------------------------------------------------------
	// �ϳ׽� ���� ���� 
	//---------------------------------------------------------------------------
	cvtColor( src , gray, CV_BGR2GRAY );							// ��ϵ� ���� ��ȯ
	resize ( gray , resize_gray , Size() , scale, scale );				// ���� ���
	Canny ( resize_gray , canny , 40 , 100 );							// ���� ����(Canny)
	
	// �������� ���� 2�� ����
	morphologyEx( canny , morph ,MORPH_DILATE , Mat() , Point(-1, -1) , 2 ); 

	//---------------------------------------------
	// ���̺� ���� - (mode=0) ���� ū ��ü ���� ������
	labeling( morph , rect, 0 );							

	//---------------------------------------------
	// ���� �ϳ׽� �簢�� ���� ũ�� ���� 
	int re_x = cvRound(rect[0].x / scale) ; 
	int re_y = cvRound(rect[0].y / scale) ; 
	int re_w = cvRound(rect[0].width / scale) ; 
	int re_h = cvRound(rect[0].height / scale) ; 

	//---------------------------------------------
	// �ϳ׽� ���� 
	Rect	harness_rect ( re_x, re_y, re_w ,re_h);			// �ϳ׽� �簢�� 
	Mat	harness_object = gray( harness_rect )	;			// ���� ������

	//---------------------------------------------
	// �߰� ���࿵�� ����
	//imshow("ĳ�Ͽ���", canny);
	//imshow("��â����", morph);
	//rectangle ( morph , rect[0] , Scalar(255) ,1)  ;
	//imshow("�󺧸�:", morph);
	//imshow("�ϳ׽�����:", harness_object);

	//---------------------------------------------------------------------------
	// ���̾� �˻� ���� ����
	//---------------------------------------------------------------------------
	// ��ü ���� 3���� 1 
	Rect sub_roi ( 0, 0 , harness_object.cols/3, harness_object.rows) ;			
	Mat  sub_object = harness_object(sub_roi).clone();
	
	//---------------------------------------------
	//// ����ȭ �� ��â ����
	threshold( sub_object , sub_object , 250 , 255 , CV_THRESH_BINARY );   //���� ���� ��ȯ
	morphologyEx( sub_object , morph , CV_MOP_DILATE , Mat() , Point(-1 , -1) , 4);

	//---------------------------------------------
	// ������ ��ġ ����
	int x1 ,y0 , y1 ;
	flip(morph, mo_flip , 1);									// ������ �� ã�� ���� ���� �¿� ����

	find_histo( morph	, x1 , VERTICAL ) ;			// ���� �������� Ŀ���� ��ġ ã��
	find_histo( morph	, y0 , HORIZONTAL ) ;		// ���� �������� Ŀ���� ���� ��ġ ã��
	find_histo( mo_flip	, y1 , HORIZONTAL ) ;	// ���� �������� Ŀ���� ������ ��ġ ã��
	y1 = (morph.cols - y1) ;					// ������ ��ġ

	//---------------------------------------------
	// Ŀ������ ������ ��� ��ǥ
	int test_region_width = 25 , margin = 15 ; 
	Point	conector_tr(x1 + margin , y0) ;

	//---------------------------------------------
	// ���̾� �˻� ���� ����
	Rect	test_roi( conector_tr , Size(test_region_width, y1)  ) ;
	Mat	test_region  	    = src (test_roi + harness_rect.tl()).clone();	 	// ���̾� ���� ����
	Mat	test_region_gray 	= gray(test_roi + harness_rect.tl()).clone();	// ��ϵ� ����

	//----------------------------------------------------------------------
	// ���� ���̾� ���� ����
	//----------------------------------------------------------------------
	vector<Rect> wire_roi = extract_wires( test_region_gray );				// ���� ���̾� ���� �簢��
	
	//---------------------------------------------
	// ���� ���̾� ���� 
	vector<Mat> wires ;
	for( int i = 0; i< (int) wire_roi.size(); i++ ) {
		wires.push_back( test_region( wire_roi[i] ) );									// �� ���̾� ���� ����
	}

	//----------------------------------------------------------------------
	// ���� ���̾� ������ ����� ���
	//----------------------------------------------------------------------
	Mat		correlation = mat_mahalanobis ( wires ) ;				// ���ҳ��Ͻ� �Ÿ� ����� ���

	//----------------------------------------------------------------------
	// ������� ���� �ҷ� �Ǻ�
	//----------------------------------------------------------------------
	Point	text_pt(100, 100);
	bool	check	= ischeck( correlation) ;									// �ҷ� �˻�
	if ( check ) {
		putText ( src, "GOOD", text_pt , FONT_HERSHEY_PLAIN,6 , CV_RGB(0 ,255, 0) , 3 );
	} 
	else {
		putText ( src, "NG" , text_pt, FONT_HERSHEY_PLAIN , 6 , CV_RGB(255, 0, 0) , 3 );
	}

	//---------------------------------------------
	// ���� ǥ��
	imshow( "display" ,  src );
//	imshow("1/3 ����:", sub_object);
//	imshow("��â����2", morph);
//	imshow("���̾�˻翵��1", test_region_gray);
//	imshow("���̾�˻翵��2", test_region);
	waitKey(0);
}
