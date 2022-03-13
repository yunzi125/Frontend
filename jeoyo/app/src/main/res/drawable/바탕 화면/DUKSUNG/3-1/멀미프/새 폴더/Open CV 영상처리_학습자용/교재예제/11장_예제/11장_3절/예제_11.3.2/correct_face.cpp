#include "preprocess.hpp"							// 검출기로드 및 전처리 함수
#include "correct_angle.hpp"						// 기울기 보정 함수들

int main()
{
	CascadeClassifier face_cascade, eyes_cascade;
	load_cascade(face_cascade, "haarcascade_frontalface_alt2.xml");
	load_cascade(eyes_cascade, "haarcascade_eye.xml");

	Mat  image = imread("../face/59.jpg", IMREAD_COLOR);
	CV_Assert(image.data);
	Mat  gray = preprocessing(image);

	vector<Rect> faces, eyes;
	vector<Point2f> eyes_center;
	face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0, Size(100, 100));

	if (faces.size() > 0)
	{
		eyes_cascade.detectMultiScale(gray(faces[0]), eyes, 1.15, 7, 0, Size(25, 20));

		if (eyes.size() == 2) {
			eyes_center.push_back(calc_center(eyes[0] + faces[0].tl()));
			eyes_center.push_back(calc_center(eyes[1] + faces[0].tl()));

			Point2d face_center = calc_center(faces[0]);
			Mat  rot_mat = calc_rotMap(face_center, eyes_center);
			Mat  correct_img = correct_image(image, rot_mat, eyes_center);

			for (size_t i = 0; i < eyes.size(); i++)
				circle(correct_img, eyes_center[i], 5, Scalar(0, 255, 0), 2);

			imshow("correct_img", correct_img);
		}
		
		waitKey();
	}
}