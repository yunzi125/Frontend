#include "preprocess.hpp"
#include "candiate.hpp"
#include "SVM.hpp"

int main()
{
	// �н������� �Ʒ�
	//Mat  trainingData, labels;
	//read_trainData("../SVMDATA.xml", trainingData, labels);
	//Ptr<ml::SVM> svm = SVM_create(CV_TERMCRIT_ITER, 1000, 0);
	//svm->train(trainingData, ml::ROW_SAMPLE, labels);	// �н�����
	
	// 	�н��� ������ �ε�
	Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("../SVMtrain.xml");

	int car_no;
	cout << "���� ���� ��ȣ (0-20) : ";
	cin >> car_no;

	string fn = format("../image/test_car/%02d.jpg", car_no);
	Mat image = imread(fn, 1);
	CV_Assert(image.data);

	Mat morph =  preprocessing(image);
	vector<RotatedRect> candidates;
	find_candidates(morph, candidates);
	vector<Mat> candidate_img = make_candidates(image, candidates);

	int plate_no = classify_plates(svm, candidate_img);

	if (plate_no >= 0)
		draw_rotatedRect(image, candidates[plate_no], Scalar(0, 255, 0), 2);

	imshow("��ȣ�ǿ���", candidate_img[plate_no]);
	imshow("image", image);
	waitKey();
	return 0; 
}

