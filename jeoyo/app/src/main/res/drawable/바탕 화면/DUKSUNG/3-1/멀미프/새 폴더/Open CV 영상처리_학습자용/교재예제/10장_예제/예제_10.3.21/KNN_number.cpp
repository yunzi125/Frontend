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
			if (!minFound){
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

	Rect middle_rect(start, number.size());			// �߽� �簢��
	Mat middle = square(middle_rect);
	number.copyTo(middle);

	resize(square, square, new_size);				// ũ�� ����
	square.convertTo(square, CV_32F);

	return square.reshape(0, 1);
}



int main() 
{
	Size  size(40, 40);			// �н� �� ũ�� 
	int  K = 15;				// �����ϴ� �̿� ���ü�
	int  Nclass = 10;			// �ν� ����(ī�װ�) ����
	int  Nsample = 20;		// ���ڴ� �н� ���ü�

	string image_file = "../image/train_numbers.png";
	Mat  train_image = imread(image_file, 0);		// ���� �ε�
	CV_Assert(train_image.data);

	threshold(train_image, train_image, 32, 255, CV_THRESH_BINARY);

	Mat  trainData, classLable;
	for (int i = 0, k = 0; i<Nclass; i++) {
		for (int j = 0; j< Nsample; j++, k++)
		{
			Point start(j * size.width, i * size.height);
			Rect  roi(start, size);
			Mat   part = train_image(roi);	// ���� ���� �и�


			Mat  num = find_number(part);	// ���� ���� ����
			Mat  data = place_middle(num, size);	// �� �߽ɿ� ���� ��ġ 
			trainData.push_back(data);		// �н� ������ ����
			classLable.push_back(i);		// ���̺�
		}
	}

	Ptr<ml::KNearest>  knn = ml::KNearest::create();
	knn->train(trainData, ml::ROW_SAMPLE, classLable);	// k-NN �н�

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++)
		{
			string demo_file = 	format("../image/demo1/%d-%02d.png", i, j);
			Mat  demo_img = imread(demo_file, 0);	// ���� �ε�
			if (demo_img.empty()) {
				cout << demo_file + " ������ �����ϴ�." << endl;
				continue;
			}

			threshold(demo_img, demo_img, 128, 255, THRESH_BINARY);
			Mat  num = find_number(demo_img);
			Mat  data = place_middle(num, size);

			Mat result;
			knn->findNearest(data, K, result);	// ���� �з� ����

			cout << "�з���� : " << result.at<float>(0) << endl;
			imshow("demo_img", demo_img);
			waitKey();
		}
	}

	return 0;
}