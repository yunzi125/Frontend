Point2f calc_center(Rect obj)
{
	Point2f c = (Point2f)obj.size() / 2.0;
	Point2f center = (Point2f)obj.tl() + c;
	return center;
}

Mat  calc_rotMap(Point2d face_center, vector<Point2f>  pt)
{
	Point2f delta = (pt[0].x > pt[1].x) ? pt[0] - pt[1] : pt[1] - pt[0];
	float  angle = fastAtan2(delta.y, delta.x);
	Mat  rot_mat = getRotationMatrix2D(face_center, angle, 1);
	return rot_mat;
}

Mat correct_image(Mat image, Mat  rot_mat, vector<Point2f>& eyes_center)
{
	Mat  correct_img;
	warpAffine(image, correct_img, rot_mat, image.size(), INTER_CUBIC);

	for (int i = 0; i < eyes_center.size(); i++)	// ´« ÁÂÇ¥ È¸Àüº¯È¯
	{
		Point3d coord(eyes_center[i].x, eyes_center[i].y, 1);
		Mat dst = rot_mat * (Mat)coord;
		eyes_center[i] = (Point2f)dst;
	}
	return correct_img;
}