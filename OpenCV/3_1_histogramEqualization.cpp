#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Provide image name to read" << endl;
		return -1;
	}

	Mat inputImg, dispImg, disp2Img, hisImg;
	inputImg = imread("C:/Users/KimDongUn/Desktop/°´Ã¼/saltAndPepper.jpg", IMREAD_UNCHANGED);
	resize(inputImg,dispImg, Size(), 0.5, 0.5, CV_INTER_AREA);
	if (inputImg.empty())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	cvtColor(dispImg, hisImg, COLOR_BGR2HLS);

	vector<Mat> channels(hisImg.channels());
	split(hisImg, channels);
	equalizeHist(channels[1], channels[1]);
	merge(channels, hisImg);
	cvtColor(hisImg, disp2Img, COLOR_HLS2BGR);

	imshow("Original", dispImg);
	imshow("Agter luminacense equalization", disp2Img);
	waitKey(0);
	return 0;
}