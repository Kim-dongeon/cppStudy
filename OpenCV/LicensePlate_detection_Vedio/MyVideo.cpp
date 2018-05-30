#include "MyVideo.hpp"

MyVideo::MyVideo()
{
}

MyVideo::MyVideo(string fname) 
{	
	cap.open(fname);	
	if (!cap.isOpened())
	{
		cout << "Error!!" << endl;
		return;
	}
	Mat temp(5, 5, CV_8U);
	kernel = temp.clone();	
}
MyVideo::~MyVideo()
{
	cap.release();	
	destroyAllWindows();
}
bool MyVideo::isFrameEmpty()
{
	if (frame.empty())
	{
		return true;
	}
	return false;
}
void MyVideo::capToFrame()
{
	cap >> frame;
}
void MyVideo::getVideoSize()
{	
	cout << "height : "<<frame.size().height << " width : " << frame.size().width << endl;
}
int MyVideo::getHeight()
{
	return frame.size().height;
}
int MyVideo::getWidth()
{
	return frame.size().width;
}

Mat MyVideo::getFrame()
{
	return frame;
}
Mat MyVideo::getFrameB()
{
//	return frame_b;
	return imageCanny;
}
void MyVideo:: drawRectangle(Mat& _frame, int frame_w, int frame_h, int rec_w, int rec_h,Scalar color, int thick)
{
	int p1_x = frame_w/2 - rec_w;
	int p1_y = frame_h / 2 - rec_h;
	int p2_x = frame_w/2 + rec_w;
	int p2_y = frame_h/2 + rec_h;
	rectangle(_frame, Point(p1_x, p1_y), Point(p2_x, p2_y), color, thick);
}

void MyVideo::frame2Gray()
{
	vector<Mat> bgr_images(3);
	split(frame, bgr_images);

	bgr_images[0] = bgr_images[2].clone();
	bgr_images[1] = bgr_images[2].clone();

	merge(bgr_images, frame);
}

void MyVideo::frame2Bin()
{	
	cvtColor(frame, frame_b, COLOR_BGR2GRAY);	
	frame_b_line = frame_b.clone();
	
	rows = frame_b.rows;
	cols = frame_b.cols;
	
	threshold(frame_b, frame_b, 128, 255, THRESH_OTSU);
	threshold(frame_b_line, frame_b_line, 128, 255, THRESH_OTSU);	
}
void MyVideo::imageProcessing()
{
	imageCanny = frame_b(Rect(cols / 2 - 80, rows / 2 - R_BIAS, cols / 2 + 80, rows / 2 + R_BIAS));
	
	morphologyEx(imageCanny, imageCanny, MORPH_TOPHAT, kernel);
	imageCanny_line = imageCanny.clone();


	Canny(imageCanny_line, imageCanny_line, 1300, 1300);
	Canny(imageCanny, imageCanny, 50, 100);
	imageCanny = imageCanny - imageCanny_line;
	morphologyEx(imageCanny, imageCanny, MORPH_TOPHAT, kernel);
	morphologyEx(imageCanny, imageCanny, MORPH_CLOSE, kernel);
}
void MyVideo::topHat(Mat& _frame_b)
{	
	morphologyEx(_frame_b, frame_b, MORPH_TOPHAT, kernel);
}

void MyVideo::blackHat(Mat _frame_b)
{
	morphologyEx(_frame_b, _frame_b, MORPH_BLACKHAT, kernel);
}

void MyVideo::detect()
{	
	findContours(imageCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point());	
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	
	ratio = 0.0;

	for (int i = 1; i < contours.size(); i++) {
		approxPolyDP(Mat(contours[i]), contours_poly[i], 1, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
	}

	for (int i = 1; i < contours.size(); i++) {
		ratio = (double)boundRect[i].width / boundRect[i].height;
		Point contours_tl = boundRect[i].tl() + Point(colBound, rowBound_t);
		Point contours_br = boundRect[i].br() + Point(colBound, rowBound_t);
		int Rect_width = boundRect[i].width;
		int Rect_height = boundRect[i].height;
		int Rect_area = boundRect[i].area();

		if (Rect_width > Rect_height &&contours_tl.y > rowBound_t &&contours_tl.x > colBound &&contours_tl.y < rowBound_b && Rect_area >80 && ratio > 1.2&&ratio < 8.0)
		{
			if (contours_tl.y < rowBound_m && contours_tl.x < colBound_m && contours_br.x > colBound_l)
			{
				if (Rect_area < 800)
				{
					rectangle(frame, contours_tl, contours_br, RED, 2, 8, 0);
				}
			}
			if (contours_tl.y > rowBound_m && contours_tl.x < colBound_m&&contours_br.x < colBound_m && contours_br.y < rowBound_b&& contours_br.x > colBound_l)	//3
			{
				if (Rect_area > 800 && ratio<3)
				{
					rectangle(frame, contours_tl, contours_br, RED, 2, 8, 0);
				}
			}
			if (contours_tl.y > rowBound_m && contours_br.x > colBound_m&& contours_tl.x < colBound_r)	//4
			{
				if ( ratio > 1.5 &&Rect_area < 3000 && contours_br.y < rowBound_b && contours_tl.x> colBound_m && ratio <6)
				{
					rectangle(frame, contours_tl, contours_br, RED, 2, 8, 0);
				}
			}
			if (contours_tl.y <rowBound_m && contours_tl.x > colBound_m && contours_tl.x < colBound_r && contours_br.y > rowBound_m)//2
			{
				if (Rect_area < 150)
				{
					rectangle(frame, contours_tl, contours_br, RED, 2, 8, 0);
				}
			}			
		}
	}
}
void MyVideo::Brightness(int n)
{
	frame = frame + Scalar(n, n, n);
}
void MyVideo::divideBlock()
{
	rowBound_t = frame.rows / 2 - R_BIAS;
	rowBound_b = rowBound_t + 100;
	rowBound_m = rowBound_t + 20;
	colBound = frame.cols / 2 - C_BIAS;
	colBound_m = frame.cols / 2 + 220;
	colBound_r = frame.cols / 2 + 440;
	colBound_l = frame.cols / 2 - 20;

}
void MyVideo::drawBolck()
{	
	line(frame, Point(0, 10), Point(10, 10), RED, 2);
	line(frame, Point(0, 20), Point(20, 20), RED, 2);
	line(frame, Point(0, rowBound_t - R_BIAS), Point(frame.cols, rowBound_t - R_BIAS), RED, 2);
	line(frame, Point(0, rowBound_b), Point(frame.cols, rowBound_b), RED, 2);
	line(frame, Point(0, rowBound_m), Point(frame.cols, rowBound_m), RED, 1);
	line(frame, Point(colBound, 0), Point(colBound, frame.rows), RED, 2);
	line(frame, Point(colBound_m, 0), Point(colBound_m, frame.rows), RED, 1);
	line(frame, Point(colBound_r, 0), Point(colBound_r, frame.rows), RED, 1);
	//line(frame, Point(colBound_l, 0), Point(colBound_l, frame.rows), RED, 1);
}

