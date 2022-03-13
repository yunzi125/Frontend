#include "preprocess.hpp"						// 검출기로드 및 전처리 함수
#include "correct_angle.hpp"					// 기울기 보정 함수들
#include "detect_area.hpp"						// 입술 및 머리영역 검출 함수
#include "histo.hpp"							// 히스토그램 비교 관련 함수
#include "classify.hpp"							// 히스토그램 비교 관련 함수

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
			cout << format("%02d영상이 없습니다.\n", no++);
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
				make_masks(sub_obj, correct_img.size(), masks);		// 4개 마스크 생성
				calc_histos(correct_img, sub_obj, hists, masks);	// 4개 히스토그램 생성
		
				classify(correct_img, hists, no);
				display(correct_img, face_center, eyes_center, sub_obj);
				imshow("correct_img", correct_img);
			}
		}
	}while (key_check(no));
}