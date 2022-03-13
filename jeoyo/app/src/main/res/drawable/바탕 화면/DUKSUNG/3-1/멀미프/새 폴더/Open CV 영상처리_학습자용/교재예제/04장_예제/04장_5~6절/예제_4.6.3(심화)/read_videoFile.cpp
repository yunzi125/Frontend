#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	FileStorage fs_r("test.xml", FileStorage::READ);
	CV_Assert(fs_r.isOpened());

	FileNode node_pic = fs_r["picture"];			// 시퀀스 노드 
	vector<Mat> images;
	for (int i = 0; i < node_pic.size(); i++) 
	{
		Mat tmp = imread("../image/" + (string)node_pic[i], IMREAD_UNCHANGED);
		CV_Assert(tmp.data);
		images.push_back(tmp);
		imshow(node_pic[i], images[i]);
	}
	fs_r.release();

	FileStorage fs_w("result.xml", FileStorage::WRITE);
	CV_Assert(fs_w.isOpened());

	vector<double> mean, dev;
	for (int i = 0; i < images.size(); i++) {
		string pic_name = ((string)node_pic[i]).substr(0,5);

		meanStdDev(images[i], mean, dev);
		fs_w << pic_name + "_mean" << "[";
		 
		for (int j = 0; j < (int)mean.size(); j++) {
			fs_w << mean[i];
		}
		fs_w << "]";
		fs_w << pic_name + "_dev" << dev;
	}

	waitKey();
	fs_w.release();
	return 0;
}