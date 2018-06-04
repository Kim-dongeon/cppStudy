#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void trackBarChanged(int value, void *)
{
	cout << "trackbar value is " << value << endl;
}

int main(int argc, char** argv)
{
	int initialValue = 100;

	Mat image = imread("C:/Users/KimDongUn/Desktop/°´Ã¼/glasses.jpg", IMREAD_UNCHANGED);
	
	imshow("MyImage", image);
	
	createTrackbar("MyTrackbar", "MyImage", &initialValue, 200, trackBarChanged);
	waitKey(0);
	return 0;
}

