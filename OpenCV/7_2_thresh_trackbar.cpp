#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void trackBarChanged(int value, void *param)
{
	cout << "trackbar value is " << value << endl;
	Mat *_grayImg = (Mat*)param;
	Mat resImg;
	threshold(*_grayImg, resImg, value, 255, CV_THRESH_BINARY);
	imshow("MyImage", resImg);
}

int main(int argc, char** argv)
{
	int initialValue = 100;

	Mat image = imread("C:/Users/KimDongUn/Desktop/°´Ã¼/glasses.jpg", IMREAD_UNCHANGED);
	Mat grayImg;
	cvtColor(image, grayImg, COLOR_BGR2GRAY);
	Mat binImg;
	threshold(grayImg, binImg, initialValue, 255, CV_THRESH_BINARY);

	imshow("MyImage", binImg);

	createTrackbar("MyTrackbar", "MyImage", &initialValue, 200, trackBarChanged,&grayImg);
	waitKey(0);
	return 0;
}

