#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


void addSaltAndPepperNoise(Mat& img, double noise_ratio)
{
	int rows = img.rows;
	int cols = img.cols;
	int ch = img.channels();
	int num_of_noise_pixels = (int)((double)(rows*cols*ch)*noise_ratio);

	for (int i = 0; i < num_of_noise_pixels; i++)
	{
		int r = rand() % rows;
		int c = rand() % cols;
		int _ch = rand() % ch;
		uchar *pixel = img.ptr<uchar>(r) + (c*ch) + _ch;

		*pixel = (rand() % 2 == 1) ? 255 : 0;
	}
}
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Provide image name to read" << endl;
		return -1;
	}

	Mat inputImg;
	Mat spImg;
	inputImg = imread(argv[1], IMREAD_UNCHANGED);
	resize(inputImg, inputImg, Size(), 0.1, 0.1, CV_INTER_AREA);
	if (inputImg.empty())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	spImg = inputImg.clone();
	addSaltAndPepperNoise(spImg, 0.35);

	Mat localAvgImg;
	Mat gaussianSmoothedImg;
	Mat medianFilteredImg;

	blur(spImg, localAvgImg, Size(5, 5));
	GaussianBlur(spImg, gaussianSmoothedImg, Size(5, 5),1.5);
	medianBlur(spImg, medianFilteredImg, 5);
	imshow("Original", inputImg);
	imshow("SaltAndPepper", spImg);
	imshow("localAvgImg", localAvgImg);
	imshow("gaussianSmoothedImg", gaussianSmoothedImg);
	imshow("medianFilteredImg", medianFilteredImg);
	

	waitKey(0);
	return 0;
}