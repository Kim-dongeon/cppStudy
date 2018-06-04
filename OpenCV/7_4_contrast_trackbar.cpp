#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void trackBarChanged(int value, void *param)
{
	Mat *_image = (Mat*)param;
	Mat resImg;
	int var_contrast = value - 100;
	double a, b;
	if (var_contrast > 0)
	{
		double delta = 127.0*var_contrast / 100.0;
		a = 255.0 / (255 - delta * 2);
		b = a * (-delta);
	}
	else
	{
		double delta = -128.0 * var_contrast / 100.0;
		a = (256.0 - delta*2.0) / 255.0;
		b = delta;
	}
	_image->convertTo(resImg, _image->type(), a, b);
	imshow("MyImage", resImg);
}

int main(int argc, char** argv)
{


	Mat image = imread("C:/Users/KimDongUn/Desktop/°´Ã¼/glasses.jpg", IMREAD_UNCHANGED);
	int initialValue = 100;
	Mat grayImg;
	cvtColor(image, grayImg, COLOR_BGR2GRAY);
	imshow("MyImage", grayImg);

	createTrackbar("MyTrackbar", "MyImage", &initialValue, 200, trackBarChanged, &grayImg);
	waitKey(0);
	return 0;
}

