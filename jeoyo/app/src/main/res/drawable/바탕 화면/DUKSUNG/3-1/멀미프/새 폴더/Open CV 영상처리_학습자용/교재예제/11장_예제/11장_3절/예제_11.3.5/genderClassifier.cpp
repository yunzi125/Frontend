#include "preprocess.hpp"						// �����ε� �� ��ó�� �Լ�
#include "correct_angle.hpp"					// ���� ���� �Լ���
#include "detect_area.hpp"						// �Լ� �� �Ӹ����� ���� �Լ�
#include "histo.hpp"							// ������׷� �� ���� �Լ�
#include "classify.hpp"							// ������׷� �� ���� �Լ�

bool key_check(int& no)
{
	int key = waitKey(0);
	if (key == 2621440) no++;
	else if (key == 2490368) no--;
	else if (key == 32 || key == 27) return false;

	return true;
}

int main()
{
	CascadeClassifier face_cascade, eyes_cascade;
	load_cascade(face_cascade, "haarcascade_frontalface_alt2.xml");
	load_cascade(eyes_cascade, "haarcascade_eye.xml");

	int no = 60;
	do{
		String fname = format("../face/%02d.jpg" , no);
		Mat  image = imread(fname, IMREAD_COLOR);
		if (image.empty()) {
			cout << format("%02d������ �����ϴ�.\n", no++);
			continue;
		}

		vector<Rect> faces, eyes, sub_obj;
		vector<Point2f> eyes_center;

		Mat  gray = preprocessing(image);
		face_cascade.detectMultiScale(gray, faces, 1.10, 3, 0, Size(100, 100));

		if (faces.size() > 0)
		{
			eyes_cascade.detectMultiScale(gray(faces[0]), eyes, 1.15, 7, 0, Size(25, 20));

			if (eyes.size() == 2) {
				eyes_center.push_back(calc_center(eyes[0] + faces[0].tl()));
				eyes_center.push_back(calc_center(eyes[1] + faces[0].tl()));

				Point2d face_center = calc_center(faces[0]);
				Mat  rot_mat = calc_rotMap(face_center, eyes_center);
				Mat  correct_img = correct_image(image, rot_mat, eyes_center);

				detect_hair(face_center, faces[0], sub_obj);
				sub_obj.push_back(detect_lip(face_center, faces[0]));

				Mat masks[4], hists[4];
				make_masks(sub_obj, correct_img.size(), masks);		// 4�� ����ũ ����
				calc_histos(correct_img, sub_obj, hists, masks);	// 4�� ������׷� ����
		
				classify(correct_img, hists, no);
				display(correct_img, face_center, eyes_center, sub_obj);
				imshow("correct_img", correct_img);
			}
		}
	}while (key_check(no));
}