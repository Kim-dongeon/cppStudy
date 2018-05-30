#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#define BLUE cv::Scalar(255,0,0)
#define GREEN cv::Scalar(0,255,0)
#define RED Scalar(0,0,255)
#define R_BIAS 20
#define C_BIAS 80
using namespace std;
using namespace cv;

class MyVideo
{
private:
	Mat frame;
	Mat frame_b;
	Mat frame_b_line;
	Mat imageROI;
	Mat	imageCanny;
	Mat imageCanny_line;
	VideoCapture cap;
	Mat kernel;
	vector <vector<Point>> contours;
	vector <Vec4i> hierarchy;	
	
	double ratio;
	int rowBound_t;
	int rowBound_b;
	int rowBound_m ;
	int colBound;
	int colBound_m;
	int colBound_r;
	int colBound_l;
	int rows; //frame.rows
	int cols; //frame.cols
	
	
public:
	MyVideo();
	MyVideo(string fname);
	~MyVideo();
	bool isFrameEmpty();
	void capToFrame();
	void getVideoSize();
	int getHeight();
	int getWidth();
	Mat getFrame();
	Mat getFrameB();	
	void frame2Gray();
	void frame2Bin();
	void drawRectangle(Mat& frame,int frame_w, int frame_h, int rec_w, int rec_h, Scalar color,int thick);
	
	void topHat(Mat& _fram_b);
	void blackHat(Mat _fram_b);	

	void detect();
	void Brightness(int n);
	void drawBolck();
	void divideBlock();
	void imageProcessing();

};