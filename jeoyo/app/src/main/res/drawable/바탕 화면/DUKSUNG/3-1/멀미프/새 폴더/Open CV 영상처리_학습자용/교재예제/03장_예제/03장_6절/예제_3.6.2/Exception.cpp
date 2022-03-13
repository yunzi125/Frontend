#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	string msg1 = "a is one.";
	string msg2 = "a is two.";
	string msg3 = "a is three.";
	int a;

	while (1){
		cout << "input a : ";
		cin >> a;

		try {
			if (a == 0)
				CV_Error(Error::StsDivByZero, "a is zero." );

			if (a == 1)
				CV_Error(Error::StsBadSize, msg1);

			if (a == 2)
				CV_Error_(Error::StsOutOfRange, ("%s : %d", msg2.c_str(), a));

			if (a == 3)
				CV_Error_(Error::StsBadArg, ("%s : %d", msg3.c_str(), a));

			CV_Assert(a != 4);
		}
		catch (cv::Exception &e) 
		{
			cout << "Exception code (" << e.code << "): " << e.what();
			cout << endl;
			if (e.code == Error::StsAssert)
				break;
		}
	}
	return 0;

}