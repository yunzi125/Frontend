#include "preprocess.hpp"

Point2d calc_center(Rect obj)							// 사각형 중심 계산	
{
	Point2d c = (Point2d)obj.size() / 2.0;
	Point2d center = (Point2d)obj.tl() + c;
	return center;
}

int main()
{
	CascadeClassifier face_cascade, eyes_cascade;
	load_cascade(face_cascade, "haarcascade_frontalface_alt2.xml");	// 정면 얼굴 검출기
	load_cascade(eyes_cascade, "haarcascade_eye.xml");			// 눈 검출기	

	Mat  image = imread("../face/w/59.jpg", IMREAD_COLOR);	// 얼굴 영상 로드
	CV_Assert(image.data);

	vector<Rect> faces, eyes;
	vector<Point2d> eyes_center;

	Mat  gray = preprocessing(image);								// 전처리
	face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0, Size(100, 100));	// 얼굴 검출

	if (faces.size() > 0)					// 얼굴 사각형 검출되면
	{	// 눈 검출 수행
		eyes_cascade.detectMultiScale(gray(faces[0]), eyes, 1.15, 7, 0, Size(25, 20));

		if (eyes.size() == 2) {							// 눈 사각형이 검출되면
			for (size_t i = 0; i < eyes.size(); i++)
			{
				Point2d center = calc_center(eyes[i] + faces[0].tl());	// 중심점 계산
				circle(image, center, 5, Scalar(0, 255, 0), 2);	// 눈 중심에 원 그리기
			}
		}

		rectangle(image, faces[0], Scalar(255, 0, 0), 2);	// 얼굴 검출 사각형 그리기
		imshow("image", image);
		waitKey();
	}
	return 0;
}