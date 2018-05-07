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

	Mat inputImg;
	inputImg = imread("C:/Users/KimDongUn/Desktop/°´Ã¼/land.png", IMREAD_UNCHANGED);
	resize(inputImg, inputImg, Size(), 0.5, 0.5, CV_INTER_AREA);
	if (inputImg.empty())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}
	vector<Mat> bgrImg(3);
	split(inputImg, bgrImg);

	imshow("Original", inputImg);
	imshow("B", bgrImg[0]);
	imshow("G", bgrImg[1]);
	imshow("R", bgrImg[2]);



	waitKey(0);
	return 0;
}