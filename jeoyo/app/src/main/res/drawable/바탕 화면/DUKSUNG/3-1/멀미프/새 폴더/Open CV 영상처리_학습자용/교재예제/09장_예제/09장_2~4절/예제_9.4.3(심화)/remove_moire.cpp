#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#include  "fft.hpp"

Mat		image, dft_coef, spectrum_img;
int		radius, thres = 120;

void remove_moire(int  value, void*  userdata)
{
	Mat remove_mask, remv_dft_coef , spectrum_tmp;

	// ���ļ� ���� ���� ����ũ ����
	threshold(spectrum_img, remove_mask, thres, 255, THRESH_TOZERO_INV);
	threshold(remove_mask, remove_mask, 1, 255, THRESH_BINARY);
	circle(remove_mask, remove_mask.size() / 2, radius, Scalar(255), -1);

	dft_coef.copyTo(remv_dft_coef, remove_mask);
	log_mag(remv_dft_coef, spectrum_tmp);				// ��Ʒ� ���ŵ� ����Ʈ��
	
	Rect img_rect(Point(0, 0), image.size());
	imshow("��Ʒ� ����", spectrum_tmp);
	imshow("�������", IFFT(remv_dft_coef, image.size()));
}

int main()
{
	image = imread("../image/mo3.jpg", 0);
	CV_Assert(image.data);

	FFT(image, dft_coef, spectrum_img);
	radius = dft_coef.rows / 4;

	imshow("image", image);
	imshow("��Ʒ� ����", spectrum_img);
	createTrackbar("������", "��Ʒ� ����", &radius, 255, remove_moire);
	createTrackbar("�Ӱ谪", "��Ʒ� ����", &thres , 255, remove_moire);
	waitKey();
	return 0;
}