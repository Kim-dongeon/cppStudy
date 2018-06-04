#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void trackBarChanged(int value, void *param)
{
	Mat *_image = (Mat*)param;
	Mat resImg;
	//value = value -100;
	_image->convertTo(resImg, _image->type(), 1.0, (double)value);
	imshow("MyImage", resImg);
}

int main(int argc, char** argv)
{
	

	Mat image = imread("C:/Users/KimDongUn/Desktop/°´Ã¼/glasses.jpg", IMREAD_UNCHANGED);
	int initialValue = 50;
	Mat resImg;
	image.convertTo(resImg, image.type(), 1.0, (double)initialValue);

	imshow("MyImage", resImg);

	createTrackbar("MyTrackbar", "MyImage", &initialValue, 255, trackBarChanged, &image);
	waitKey(0);
	return 0;
}

