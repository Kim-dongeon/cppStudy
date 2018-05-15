#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat inputImg, dispImg;
	Mat grayImg, binImg;
	inputImg = imread("C:/Users/KimDongUn/Desktop/°´Ã¼/saltAndPepper.jpg", IMREAD_UNCHANGED);
	resize(inputImg, dispImg, Size(), 0.2, 0.2, CV_INTER_AREA);
	if (inputImg.empty())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	cvtColor(dispImg, grayImg, COLOR_BGR2GRAY);
	adaptiveThreshold(grayImg, binImg,  255, ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,7,3.0);	//ÁÖº¯ÀÇ ÇÈ¼¿ °ª°ú °¡ÁßÆò±ÕÀ» ³»¼­ 5=Æò±ÕÀ» ³¾ ÀÌ¿ôÇÈ¼¿ÀÇ °³¼ö(25°³),ÁÖº¯°ú Æò±Õº¸´Ù 3.0Â÷ÀÌ°¡ ³ª¸é ¹Ù²ï´Ù.
	imshow("Original", dispImg);
	imshow("Gray", grayImg);
	imshow("Binary", binImg);
	waitKey(0);
	return 0;
}