#include "preprocess.hpp"						// 검출기로드 및 전처리 함수
#include "correct_angle.hpp"					// 기울기 보정 함수들
#include "detect_area.hpp"						// 입술 및 머리영역 검출 함수
#include "histo.hpp"							// 히스토그램 비교 관련 함수

int main()
{
	CascadeClassifier face_cascade, eyes_cascade;
	load_cascade(face_cascade, "haarcascade_frontalface_alt2.xml");
	load_cascade(eyes_cascade, "haarcascade_eye.xml");

	Mat  image = imread("../face/59.jpg", IMREAD_COLOR);
	CV_Assert(image.data);
	Mat  gray = preprocessing(image);

	vector<Rect> faces, eyes, sub_obj;
	vector<Point2f> eyes_center;
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
			
		  // 히스토그램 비교 - 유사도 값
			double criteria1 = compareHist(hists[0], hists[1], CV_COMP_CORREL);
			double criteria2 = compareHist(hists[2], hists[3], CV_COMP_CORREL);
			
			cout << format("머리부분 유사도 %4.2f\n", criteria1);
			cout << format("입술부분 유사도 %4.2f\n", criteria2);
		}
	}
	return 0;
}