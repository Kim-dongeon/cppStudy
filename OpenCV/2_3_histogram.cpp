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
	resize(inputImg, inputImg, Size(), 0.2, 0.2, CV_INTER_AREA);
	if (inputImg.empty())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}
	
	MatND histogramB, histogramG, histogramR;
	const int channel_numbersB[] = { 0 };
	const int channel_numbersG[] = { 1 };
	const int channel_numbersR[] = { 2 };
	float channel_range[] = { 0.0, 255.0 };
	const float* channel_ranges = channel_range;
	int number_bins = 255;

	calcHist(&inputImg, 1, channel_numbersB, Mat(), histogramB, 1, &number_bins, &channel_ranges);
	calcHist(&inputImg, 1, channel_numbersG, Mat(), histogramG, 1, &number_bins, &channel_ranges);
	calcHist(&inputImg, 1, channel_numbersR, Mat(), histogramR, 1, &number_bins, &channel_ranges);
	
	//Plot the histogram
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / number_bins);

	Mat histImageB(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	Mat histImageG(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	Mat histImageR(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(histogramB, histogramB, 0, histImageB.rows, NORM_MINMAX, -1, Mat());
	normalize(histogramG, histogramG, 0, histImageG.rows, NORM_MINMAX, -1, Mat());
	normalize(histogramR, histogramR, 0, histImageR.rows, NORM_MINMAX, -1, Mat());
	
	for (int i = 1; i < number_bins; i++)
	{
		line(histImageB, Point(bin_w*(i -1), hist_h - cvRound(histogramB.at<float>(i-1))),
			Point(bin_w*(i), hist_h - cvRound(histogramB.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImageG, Point(bin_w*(i - 1), hist_h - cvRound(histogramG.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(histogramG.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImageR, Point(bin_w*(i - 1), hist_h - cvRound(histogramR.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(histogramR.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}
	
	imshow("Original", inputImg);
	imshow("HistogramB", histImageB);
	imshow("HistogramG", histImageG);
	imshow("HistogramR", histImageR);
	waitKey(0);
	return 0;
}