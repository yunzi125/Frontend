#include "kNN.hpp"

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
	for (int i = 0, k = 0; i < Nclass; i++) {
		for (int j = 0; j < Nsample; j++, k++)
		{
			Point start(j * size.width, i * size.height);
			Rect  roi(start, size);
			Mat   part = train_image(roi);			// ���� ���� �и�

			Mat  num = find_number(part);		// ���� ���� ����
			Mat  data = place_middle(num, size);	// ����ȭ �� 1�൥���� ����
			trainData.push_back(data);		// �н� ������ ����
			classLable.push_back(i);		// ���̺�
		}
	}

	Ptr<ml::KNearest>  knn = ml::KNearest::create();
	knn->train(trainData, ml::ROW_SAMPLE, classLable);	// k-NN �н�


	int no;
	cout << "�����ȣ�� �Է��ϼ���: ";
	cin >> no;									// �����ȣ �Է�

	string demo_file = format("../image/num/%02d.png", no);
	Mat  test_img = imread(demo_file, 0);			// ���� ���� �ε�
	CV_Assert(test_img.data);						// ����ó��

	threshold(test_img, test_img, 128, 255, THRESH_BINARY);	// ����ȭ
	Mat  num = find_number(test_img);				// ���ڰ�ü ����
	Mat  data = place_middle(num, size);			// ���ڰ�ü �� �߽� ��ġ 

	Mat result;
	knn->findNearest(data, K, result);				// ���� �з� ����

	cout << "�з���� : " << result.at<float>(0) << endl;
	imshow("test_img", test_img);
	waitKey();
	return 0; 
}