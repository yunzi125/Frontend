#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void find_histoPos(Mat img, int & start, int &end, int direct)
{
	reduce(img, img, direct, REDUCE_AVG);

	int  minFound = 0;
	for (int i = 0; i< (int)img.total(); i++) {
		if (img.at<uchar>(i) < 250) 		// ������� �ƴϸ�
		{
			end = i;					// ������׷� ������ ��ġ
			if (!minFound) {
				start = i;			// ������׷� ù ��ġ
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

	return part(Rect(start, end));			// ���ڰ�ü ����
}

Mat  place_middle(Mat number, Size new_size)
{
	int  big = max(number.cols, number.rows);
	Mat  square(big, big, number.type(), Scalar(255));	// ���濵��

	Point start = (square.size() - number.size()) / 2;
	Rect middle(start, number.size());					// �߾� ���ɿ���
	number.copyTo(square(middle));						// ���ڰ�ü�� �߾ӿ� ����	
	
	resize(square, square, new_size);					// ũ�� ����
	square.convertTo(square, CV_32F);
	return square.reshape(0, 1);						// 1�� ������ ������ ��ȯ
}

