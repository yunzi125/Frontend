#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

vector<Point2f> findImageCorners(Mat image, Size boardSize)
{
	static int cnt = 0;
	vector<Point2f> imgPoints;
	Mat gray;
	cvtColor(image, gray, CV_RGB2GRAY);
	bool found = findChessboardCorners(gray, boardSize, imgPoints);

	if (found) {
		cornerSubPix(gray, imgPoints, Size(11, 11), Size(-1, -1),
			TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.1));

		drawChessboardCorners(image, boardSize, imgPoints, found);
		imshow("image_" + to_string(cnt), image);
		waitKey();
		destroyWindow("image_" + to_string(cnt++));
	}

	return imgPoints;
}

vector<Point3f> calcObjectCorners(Size boardSize, float squareSize)
{
	vector<Point3f> corners;
	for (int i = 0; i < boardSize.height; i++)
		for (int j = 0; j < boardSize.width; j++)
		{
			float x = float(j*squareSize);
			float y = float(i*squareSize);
			corners.push_back(Point3f(x, y, 0));
		}

	return corners;
}

int main()
{
	Size boardSize(8, 7), imageSize;
	float squareSize = 1.f;

	vector<String> filelist;
	filelist.push_back("../image/chessboard_01.jpg");
	filelist.push_back("../image/chessboard_02.jpg");
	filelist.push_back("../image/chessboard_03.jpg");

	vector<vector<Point2f>> imagePoints;
	vector<vector<Point3f>> objectPoints;

	for (int i = 0; i < filelist.size(); i++)
	{
		Mat image = imread(filelist[i], 1);
		CV_Assert(image.data);

		vector<Point2f> imgPoints = findImageCorners(image, boardSize);

		if (!imgPoints.empty())
		{
			vector<Point3f> objPoints = calcObjectCorners(boardSize, squareSize);

			imagePoints.push_back(imgPoints);
			objectPoints.push_back(objPoints);
		}
	}

	vector<Mat> rvecs, tvecs;
	Mat cameraMatrix, distCoeffs;
	Mat undistorted;

	Mat image = imread("../image/chessboard_05.jpg", 1);
	CV_Assert(image.data);

	double rms = calibrateCamera(objectPoints, imagePoints, image.size(),
		cameraMatrix, distCoeffs, rvecs, tvecs);

	undistort(image, undistorted, cameraMatrix, distCoeffs);

	cout << "cameraMatrix " << endl << cameraMatrix << endl << endl;
	printf("RMS error reported by calibrateCamera: %g\n", rms);

	imshow("Original", image);
	imshow("Undistorted", undistorted);
	waitKey();
}