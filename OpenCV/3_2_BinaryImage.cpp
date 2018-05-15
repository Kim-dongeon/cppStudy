#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat inputImg, dispImg;
	Mat grayImg, binImg;
	inputImg = imread("C:/Users/KimDongUn/Desktop/��ü/dark.PNG", IMREAD_UNCHANGED);
	resize(inputImg, dispImg, Size(), 1, 1, CV_INTER_AREA);
	if (inputImg.empty())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	cvtColor(dispImg, grayImg, COLOR_BGR2GRAY);
	//threshold(grayImg, binImg, 128, 255, THRESH_BINARY);
	//threshold(grayImg, binImg, 128, 255, THRESH_OTSU);//������׷��� �м��Ͽ� ��κа� ��ο� �κ� ����� �ڸ���.
	adaptiveThreshold(grayImg, binImg, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 3.0);
	imshow("Original", dispImg);
	imshow("Gray",grayImg);
	imshow("Binary", binImg);
	waitKey(0);
	return 0;
}