#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void find_histoPos(Mat img, int & start, int &end, int direct)
{
	reduce(img, img, direct, REDUCE_AVG);

	int  minFound = 0;
	for (int i = 0; i< (int)img.total(); i++) {
		if (img.at<uchar>(i) < 250) 		// 빈라인이 아니면
		{
			end = i;					// 히스토그램 마지막 위치
			if (!minFound) {
				start = i;			// 히스토그램 첫 위치
				minFound = 1;
			}
		}
	}
}

Mat find_number(Mat part)
{
	Point start, end;
	find_histoPos(part, start.x, end.x, 0);		// 수직 투영 
	find_histoPos(part, start.y, end.y, 1);   	// 수평 투영 

	return part(Rect(start, end));			// 숫자객체 영상
}

Mat  place_middle(Mat number, Size new_size)
{
	int  big = max(number.cols, number.rows);
	Mat  square(big, big, number.type(), Scalar(255));	// 정방영상

	Point start = (square.size() - number.size()) / 2;
	Rect middle(start, number.size());					// 중앙 관심영역
	number.copyTo(square(middle));						// 숫자객체를 중앙에 복사	
	
	resize(square, square, new_size);					// 크기 변경
	square.convertTo(square, CV_32F);
	return square.reshape(0, 1);						// 1행 데이터 변경후 반환
}

