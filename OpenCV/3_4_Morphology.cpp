#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat inputImg, dispImg;
	Mat grayImg, binImg;
	inputImg = imread("C:/Users/KimDongUn/Desktop/��ü/land.PNG", IMREAD_UNCHANGED);
	resize(inputImg, dispImg, Size(), 0.8, 0.8, CV_INTER_AREA);
	if (inputImg.empty())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	cvtColor(dispImg, grayImg, COLOR_BGR2GRAY);
	//adaptiveThreshold(grayImg, binImg, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, 3.0);	//�ֺ��� �ȼ� ���� ��������� ���� 5=����� �� �̿��ȼ��� ����(25��),�ֺ��� ��պ��� 3.0���̰� ���� �ٲ��.
	threshold(grayImg, binImg, 128, 255, THRESH_OTSU);
	//threshold(grayImg, binImg, 128, 255, THRESH_BINARY);
	
	/*dilation	��� �κ��� Ȯ��ȴ�. kernel�� Ŀ�� ���� �� �κ��� Ŀ����.
	Mat dilatedImg;
	Mat kernel(3, 3, CV_8U);
	dilate(binImg, dilatedImg, kernel);
	*/
	/*erosion
	Mat erodeImg;
	Mat kernel(5, 5, CV_8U);
	erode(binImg, erodeImg, kernel);
	*/
	Mat openImg,closeImg;
	Mat kernel(3, 3, CV_8U);
	morphologyEx(binImg, openImg, MORPH_OPEN, kernel);
	morphologyEx(binImg, closeImg, MORPH_CLOSE, kernel);
	imshow("Original", dispImg);
	imshow("bin", binImg);
	imshow("open", openImg);
	imshow("close", closeImg);
	waitKey(0);
	return 0;
}