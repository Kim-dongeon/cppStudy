#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat inputImg, dispImg;
	Mat grayImg, binImg;
	inputImg = imread("C:/Users/KimDongUn/Desktop/객체/dark.PNG", IMREAD_UNCHANGED);
	resize(inputImg, dispImg, Size(), 1, 1, CV_INTER_AREA);
	if (inputImg.empty())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	cvtColor(dispImg, grayImg, COLOR_BGR2GRAY);
	//threshold(grayImg, binImg, 128, 255, THRESH_BINARY);
	//threshold(grayImg, binImg, 128, 255, THRESH_OTSU);//히스토그램을 분석하여 흰부분과 어두운 부분 가운데를 자른다.
	adaptiveThreshold(grayImg, binImg, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 3.0);
	imshow("Original", dispImg);
	imshow("Gray",grayImg);
	imshow("Binary", binImg);
	waitKey(0);
	return 0;
}