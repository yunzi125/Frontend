#include "preprocess.hpp"

Point2d calc_center(Rect obj)							// �簢�� �߽� ���	
{
	Point2d c = (Point2d)obj.size() / 2.0;
	Point2d center = (Point2d)obj.tl() + c;
	return center;
}

int main()
{
	CascadeClassifier face_cascade, eyes_cascade;
	load_cascade(face_cascade, "haarcascade_frontalface_alt2.xml");	// ���� �� �����
	load_cascade(eyes_cascade, "haarcascade_eye.xml");			// �� �����	

	Mat  image = imread("../face/w/59.jpg", IMREAD_COLOR);	// �� ���� �ε�
	CV_Assert(image.data);

	vector<Rect> faces, eyes;
	vector<Point2d> eyes_center;

	Mat  gray = preprocessing(image);								// ��ó��
	face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0, Size(100, 100));	// �� ����

	if (faces.size() > 0)					// �� �簢�� ����Ǹ�
	{	// �� ���� ����
		eyes_cascade.detectMultiScale(gray(faces[0]), eyes, 1.15, 7, 0, Size(25, 20));

		if (eyes.size() == 2) {							// �� �簢���� ����Ǹ�
			for (size_t i = 0; i < eyes.size(); i++)
			{
				Point2d center = calc_center(eyes[i] + faces[0].tl());	// �߽��� ���
				circle(image, center, 5, Scalar(0, 255, 0), 2);	// �� �߽ɿ� �� �׸���
			}
		}

		rectangle(image, faces[0], Scalar(255, 0, 0), 2);	// �� ���� �簢�� �׸���
		imshow("image", image);
		waitKey();
	}
	return 0;
}