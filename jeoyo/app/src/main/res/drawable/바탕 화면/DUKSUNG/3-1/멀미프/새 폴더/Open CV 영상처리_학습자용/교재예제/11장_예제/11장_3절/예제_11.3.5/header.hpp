void load_cascade(CascadeClassifier& cascade, string fname)
{
	String  path = "C:/opencv3.0/sources/data/haarcascades/";
	String  full_name = path + fname;

	CV_Assert(cascade.load(full_name));
}

Mat preprocessing(Mat frame)
{
	Mat frame_gray;
	cvtColor(frame, frame_gray, CV_BGR2GRAY);

	equalizeHist(frame_gray, frame_gray);
	return frame_gray;
}

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

Mat correct_image(Mat image, Point2f face_center, vector<Point2f>& eyes_center)
{
	Mat  correct_img;
	Mat  rot_mat = calc_rotMap(face_center, eyes_center);
	warpAffine(image, correct_img, rot_mat, image.size(), INTER_CUBIC);

	for (int i = 0; i < eyes_center.size(); i++)
	{
		Mat coord = (Mat_<double>(3, 1) << eyes_center[i].x, eyes_center[i].y, 1);
		Mat dst = rot_mat * coord;
		eyes_center[i] = (Point2f)dst;
	}

	return correct_img;
}

Rect detect_lip(Point2d face_center, Rect face){

	Point2d lip_center = face_center + Point2d(0, face.height*0.30);
	Point2d gap_size(face.width * 0.18, face.height * 0.1);

	Point  lip_start = lip_center - gap_size;
	Point  lip_end = lip_center + gap_size;

	return Rect(lip_start, lip_end);
}

vector<Rect2d>  detect_hair(Point2d face_center, Rect face)
{
	Point2d  h_gap_size(face.width *0.45, face.height*0.65);
	Point2d  pt1 = face_center - h_gap_size;
	Point2d  pt2 = face_center + h_gap_size;
	Rect2d   hair = Rect2d(pt1, pt2);

	Size2d  size(hair.width, hair.height * 0.41);
	Rect2d  hair1 = Rect2d(hair.tl(), size);
	Rect2d  hair2 = Rect2d(hair.br() - (Point2d)size, size);

	vector<Rect2d> hair_rect;
	hair_rect.push_back(hair1);
	hair_rect.push_back(hair2);
	hair_rect.push_back(hair);

	return  hair_rect;
}

void calc_histo(const Mat& img, Mat& hist, Vec3i bins, Vec3f range, Mat mask, int _dims = 3)
{
	int 	dims = (_dims <= 0) ? img.channels() : _dims;
	int		channels[] = { 0, 1, 2 };
	int		histSize[] = { bins[0], bins[1], bins[2] };

	float  range1[] = { 0, range[0] };
	float  range2[] = { 0, range[1] };
	float  range3[] = { 0, range[2] };
	const float* ranges[] = { range1, range2, range3 };			// 모든 채널 화소범위

	calcHist(&img, 1, channels, mask, hist, dims, histSize, ranges);
}


void calc_histo_hsv(const Mat& img, Mat& hist, Vec3i bins, Vec3f range, Mat mask, int _dims)
{
	int 	dims = (_dims <= 0) ? img.channels() : _dims;
	int		channels[] = { 0, 1, 2 };
	int		histSize[] = { bins[0], bins[1], bins[2] };

	float  range1[] = { 0, range[0] };
	float  range2[] = { 0, range[1] };
	float  range3[] = { 0, range[2] };
	const float* ranges[] = { range1, range2, range3 };			// 모든 채널 화소범위

	Mat hsv;
	cvtColor(img, hsv, CV_BGR2HSV);

	calcHist(&hsv, 1, channels, mask, hist, dims, histSize, ranges);
	normalize(hist, hist, 0, 1, NORM_MINMAX);
}


void draw_ellipse(Mat& image, Rect2d rect, Scalar color, int thickness, float ratio)
{
	Point2d center = rect.tl() + (Point2d)rect.size() * 0.5;
	Size2d size = (Size2d)rect.size() * 0.45;
	ellipse(image, center, size, 0, 0, 360, color, thickness);
}


void make_masks(vector<Rect2d> sub_obj, Size org_size, Mat masks[4])
{
	Mat base_mask(org_size, CV_8U, Scalar(0));
	draw_ellipse(base_mask, sub_obj[2], Scalar(255), -1, 0.45f);

	masks[0] = ~base_mask(sub_obj[0]);
	masks[1] = ~base_mask(sub_obj[1]);

	draw_ellipse(base_mask, sub_obj[3], Scalar(0), -1, 0.45f);
	masks[3] = ~base_mask(sub_obj[3]);
	masks[2] = base_mask(sub_obj[2]);
}

void campare_hist(Mat  correct_img, vector<Rect2d> sub_obj, double criteria[2])
{
	Mat  hists[4], masks[4];
	Vec3i bins(64, 64, 64);
	Vec3f ranges(256, 256, 256);

	make_masks(sub_obj, correct_img.size(), masks);

	for (int i = 0; i < (int)sub_obj.size(); i++)
	{
		Mat sub = correct_img(sub_obj[i]);
		calc_histo(sub, hists[i], bins, ranges, masks[i]);
//		imshow(format("mask[%d]",i), masks[i]);
	}

	criteria[0] = compareHist(hists[0], hists[1], CV_COMP_CORREL);		//유사도 비교값
	criteria[1] = compareHist(hists[2], hists[3], CV_COMP_CORREL);		
}

bool key_check(int& no)
{
	int key = waitKey(0);
	if (key == 2621440) no++;
	else if (key == 2490368) no--;
	else if (key == 32 || key == 27)		return false;

	return true;
}


void classify(Mat& image, double criteria[2], int no)
{
	double tmp = (criteria[0] > 0.2) ? 0.2 : 0.4;
	int value = (criteria[1] > tmp) ? 0 : 1;

	string text = (value) ? "Man" : "Woman";
	text = format("%02d.jpg: ", no) + text;

	int font = FONT_HERSHEY_TRIPLEX;
	putText(image, text, Point(12, 31), font, 0.7, Scalar(0, 0, 0), 2);
	putText(image, text, Point(10, 30), font, 0.7, Scalar(0, 255, 0), 1);

	cout << text;
	cout << format(" - 유사도 [머리: %4.2f  입술: %4.2f]\n", criteria[0], criteria[1]);
}


void display(Mat &image, Point2d face_center, vector<Point2f> eye_center, vector<Rect2d> sub_obj)
{
	circle(image, eye_center[0], 10, Scalar(0, 255, 0), 2);
	circle(image, eye_center[1], 10, Scalar(0, 255, 0), 2);
	circle(image, face_center, 3, Scalar(0, 0, 255), 2);

	draw_ellipse(image, sub_obj[2], Scalar(255, 100, 0), 2, 0.45f);
	draw_ellipse(image, sub_obj[3], Scalar(0, 0, 255), 2, 0.45f);
}