#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	while(1)
	{
		int no;
		cout << "���� ���� ��ȣ( 0:���� ) : ";
		cin >> no;
		if (no == 0) break;

		string fname = format("../test_car/%02d.jpg", no);
		Mat image = imread(fname, 1); 
		if (image.empty()) {
			cout << to_string(no) + "�� ���� ������ �����ϴ�. " << endl;
			continue;
		}

		Mat gray, sobel, th_img, morph;
		Mat kernel(5, 31, CV_8UC1, Scalar(1));		// ���� ���� ����ũ
		cvtColor(image, gray, CV_BGR2GRAY);		// ��ϵ� ���� ��ȯ

		blur(gray, gray, Size(5, 5));					// ����
		Sobel(gray, gray, CV_8U, 1, 0, 3);			// �Һ� ���� ����

		threshold(gray, th_img, 120, 255, THRESH_BINARY);	// ����ȭ ����
		morphologyEx(th_img, morph, MORPH_CLOSE, kernel);	// ���� ���� ����

		imshow("image", image);
		imshow("���� ����", th_img), imshow("���� ����", morph);
		waitKey();
	} 
	return 0;
}