#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat inputImg, dispImg;
	Mat grayImg, binImg;
	inputImg = imread("C:/Users/KimDongUn/Desktop/객체/land.PNG", IMREAD_UNCHANGED);
	resize(inputImg, dispImg, Size(), 0.8, 0.8, CV_INTER_AREA);
	if (inputImg.empty())
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	// 세가지 색을 동일하게 -> gray 이미지가 된다.
	vector<Mat> bgr_images(3);
	split(inputImg, bgr_images);


	bgr_images[0] = bgr_images[2].clone();
	bgr_images[1] = bgr_images[2].clone();
	
	Mat switchedImg;
	merge(bgr_images, switchedImg);
	//circle(switchedImg, Point(250, 250), 200, Scalar(0, 0, 255), 4, 8, 0); //회색 img위에 빨간 원그리기

	for (int row = 0; row < inputImg.rows; row++)		//세로
	{
		for (int col = 0; col < inputImg.cols; col++)		//가로
		{
			uchar B = inputImg.at<Vec3b>(row, col)[0];
			uchar G = inputImg.at<Vec3b>(row, col)[1];
			uchar R = inputImg.at<Vec3b>(row, col)[2];

			if (B > 130 && G<40 && R<40  )
			{
				switchedImg.at<Vec3b>(row, col)[0] = B;
				switchedImg.at<Vec3b>(row, col)[1] = G;
				switchedImg.at<Vec3b>(row, col)[2] = R;
			}

		}
	}
	imshow("Original", inputImg);
	imshow("Switched", switchedImg);
	
	/*
	#define FROM 0
	#define TO 2
	Mat temp;
	temp = bgr_images[FROM];
	bgr_images[FROM] = bgr_images[TO];
	bgr_images[TO] = temp;

	Mat switchedImg;
	merge(bgr_images, switchedImg);
	imshow("Original", inputImg);
	imshow("Switched", switchedImg);*/
	
	
	
	/*
	bgr_images[0] = Mat::ones(bgr_images[0].size(), bgr_images[0].type())*255.0;
	bgr_images[2] = Mat::zeros(bgr_images[2].size(), bgr_images[2].type());
	Mat onOffImg;
	merge(bgr_images, onOffImg);

	imshow("Original", inputImg);
	imshow("onOff", onOffImg);*/
	waitKey(0);
	return 0;
}