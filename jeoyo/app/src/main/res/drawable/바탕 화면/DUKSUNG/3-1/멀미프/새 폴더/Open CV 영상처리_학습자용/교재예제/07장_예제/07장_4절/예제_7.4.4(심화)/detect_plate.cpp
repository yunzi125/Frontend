#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	while(1)
	{
		int no;
		cout << "차량 영상 번호( 0:종료 ) : ";
		cin >> no;
		if (no == 0) break;

		string fname = format("../test_car/%02d.jpg", no);
		Mat image = imread(fname, 1); 
		if (image.empty()) {
			cout << to_string(no) + "번 영상 파일이 없습니다. " << endl;
			continue;
		}

		Mat gray, sobel, th_img, morph;
		Mat kernel(5, 31, CV_8UC1, Scalar(1));		// 닫임 연산 마스크
		cvtColor(image, gray, CV_BGR2GRAY);		// 명암도 영상 변환

		blur(gray, gray, Size(5, 5));					// 블러링
		Sobel(gray, gray, CV_8U, 1, 0, 3);			// 소벨 에지 검출

		threshold(gray, th_img, 120, 255, THRESH_BINARY);	// 이진화 수행
		morphologyEx(th_img, morph, MORPH_CLOSE, kernel);	// 열림 연산 수행

		imshow("image", image);
		imshow("이진 영상", th_img), imshow("열림 연산", morph);
		waitKey();
	} 
	return 0;
}