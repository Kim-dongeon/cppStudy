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

	inputImg = imread(argv[1], IMREAD_UNCHANGED);

	if (inputImg.empty())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	Mat resizedOne;
	resize(inputImg, resizedOne, Size(), 2.0, 2.0);
	imshow("Original", resizedOne);

	waitKey(2000);
	return 0;
}