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
//	return imageROI;
//	return imageCanny_line;
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
	//int start = frame.size().height / 2;
	//int end = frame.size().height;
	//int width = frame.size().width;
	//
	//for (int row = start; row < end; row++)		//세로
	//{
	//	for (int col = 0; col < width; col++)		//가로
	//	{			
	//		uchar H = frame.at<Vec3b>(row, col)[0];
	//		uchar L = frame.at<Vec3b>(row, col)[1];
	//		uchar S = frame.at<Vec3b>(row, col)[2];
	//		if (col == 1055 && row == 420)
	//		{
	//			cout << (int)H <<", "<<(int)L <<", "<<(int)S<< endl;
	//		}
	//		
	//		if (L > 200 && H<100 && S <100)
	//		{
	//			frame.at<Vec3b>(row, col) = Vec3b(255, 255, 255);
	//		}
	//	}
	//}
	cvtColor(frame, frame_b, COLOR_BGR2GRAY);
	//cvtColor(frame, frame_b_line, COLOR_BGR2GRAY);
	
	frame_b_line = frame_b.clone();
	//morphologyEx(frame_b, frame_b, MORPH_TOPHAT, kernel);
	//morphologyEx(frame_b_line, frame_b_line, MORPH_TOPHAT, kernel);
	int rows = frame_b.rows;
	int cols = frame_b.cols;
	
	threshold(frame_b, frame_b, 128, 255, THRESH_OTSU);
	threshold(frame_b_line, frame_b_line, 128, 255, THRESH_OTSU);
	//threshold(frame_b, frame_b, 30, 255, THRESH_BINARY);
	//threshold(frame_b_line, frame_b_line, 20, 255, THRESH_BINARY);
	/*morphologyEx(frame_b, frame_b, MORPH_TOPHAT, kernel);	
	morphologyEx(frame_b_line, frame_b_line, MORPH_TOPHAT, kernel);*/

	imageCanny = frame_b(Rect(cols/2-80, rows/2- R_BIAS, cols/2+80, rows /2+ R_BIAS));
	//imageCanny_line = frame_b_line(Rect(cols / 2 - C_BIAS, rows/2- R_BIAS, cols / 2 + C_BIAS, rows/2+ R_BIAS));
	morphologyEx(imageCanny, imageCanny, MORPH_TOPHAT, kernel);
	//morphologyEx(imageCanny_line, imageCanny_line, MORPH_TOPHAT, kernel);
	imageCanny_line = imageCanny.clone();
	////cout << imageCanny.rows << " " << cols << endl;

	Canny(imageCanny_line, imageCanny_line, 1300,1300);
	Canny(imageCanny, imageCanny, 50,100);
	//morphologyEx(imageCanny_line, imageCanny_line, MORPH_CLOSE, kernel);
	imageCanny = imageCanny - imageCanny_line;
	//morphologyEx(frame_b, frame_b, MORPH_DILATE, kernel);
	morphologyEx(imageCanny, imageCanny, MORPH_TOPHAT, kernel);
	morphologyEx(imageCanny, imageCanny, MORPH_CLOSE, kernel);
	//morphologyEx(frame_b, frame_b, MORPH_DILATE, kernel);
	//morphologyEx(imageCanny, imageCanny, MORPH_DILATE, kernel);




	//morphologyEx(imageCanny, imageCanny, MORPH_ERODE, kernel);
	//for (int i = 0; i < rows; i++)
	//{
	//	for (int j = 0; j < cols; j++)
	//	{
	//		if (i < rows/2 - 20)
	//		{
	//			frame_b.at<uchar>(i, j) = uchar(0);
	//		}
	//		else if (j < cols / 2 - 80)
	//		{
	//			frame_b.at<uchar>(i, j) = uchar(0);
	//		}
	//	}		
	//}
	//Canny(frame_b, frame_b, 100, 200);
	
	//
	//imageROI = Mat::zeros(Size(cols,rows), CV_8UC3);
	//cvtColor(imageROI, imageROI, COLOR_BGR2GRAY);
	//Canny(imageROI, imageROI, 100, 200);
	//Canny(frame_b, frame_b, 100, 200);
	////cout << rows << " " << cols << endl;
	//int x = 0, y = 0;
	/*for (int i = rows/2;i < rows ; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			imageROI.at<uchar>(i,j) += imageCanny.at<uchar>(i, j);
			y++;
		}
		x++;
	}*/

	//cout << imageROI.rows << " " << imageROI.cols << endl;
	
//	GaussianBlur(frame_b, frame_b, Size(3, 3), 0);

//	adaptiveThreshold(frame_b, frame_b, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 3.0);
//	threshold(frame_b, frame_b, 128, 255, THRESH_OTSU);
	//morphologyEx(frame_b, frame_b, MORPH_TOPHAT, kernel);
	//adaptiveThreshold(frame_b, frame_b, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 3.0);
//	Canny(frame_b, imageCanny, (rows + cols) / 4, (rows + cols) / 2);
//	Canny(frame_b, imageCanny,600,600);
//	cout << imageCanny.rows << " " << cols << endl; 
//	Canny(frame_b,frame_b, 100,600);
//	Canny(frame_b, frame_b, 300, 600);

	
	//threshold(frame_b, imageCanny, 120, 255, THRESH_BINARY);
	//threshold(frame_b, frame_b, 100, 255, THRESH_BINARY);
	
//	frame_b = frame_b - imageCanny;
}

void MyVideo::topHat(Mat& _frame_b)
{	
//	adaptiveThreshold(frame_b, frame_b, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 0.0);
	morphologyEx(_frame_b, frame_b, MORPH_TOPHAT, kernel);
//	threshold(frame_b, frame_b, 128, 255, THRESH_OTSU);
	
	//threshold(frame_b, frame_b, 20, 255, THRESH_BINARY);
//	morphologyEx(_frame_b, frame_b, MORPH_CLOSE, Mat(5, 5, CV_8U));
//	threshold(frame_b, frame_b, 128, 255, THRESH_OTSU);
//	adaptiveThreshold(frame_b, frame_b, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 101, 0.0);
//	morphologyEx(_frame_b, frame_b, MORPH_CLOSE, Mat(5, 5, CV_8U));
	
	
//	threshold(frame_b, frame_b, 128, 255, THRESH_OTSU);	
	//threshold(frame_b,frame_b, 100, 255, THRESH_BINARY);
//	morphologyEx(_frame_b, frame_b, MORPH_CLOSE, kernel);
}

void MyVideo::blackHat(Mat _frame_b)
{
	morphologyEx(_frame_b, _frame_b, MORPH_BLACKHAT, kernel);
}

void MyVideo::detect()
{
	//findContours(frame_b, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point());
	findContours(imageCanny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point());
	//cout<<contours.size()<<endl;
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Rect> boundRect2(contours.size());
	refinery_count = 0;
	ratio = 0.0;

	for (int i = 1; i < contours.size(); i++) {
		approxPolyDP(Mat(contours[i]), contours_poly[i], 1, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
	}
	int rowBound_t = frame.rows / 2 - R_BIAS;
	int rowBound_b = rowBound_t + 100;
	int rowBound_m = rowBound_t + 20;
	int colBound = frame.cols / 2 - C_BIAS;
	int colBound_m = frame.cols / 2 +220;
	int colBound_r = frame.cols / 2 + 440;
	int colBound_l = frame.cols / 2 - 20;
//	line(frame, Point(0, 10), Point(10, 10), RED, 2);
//	line(frame, Point(0, 20), Point(20, 20), RED, 2);
	line(frame, Point(0, rowBound_t- R_BIAS), Point(frame.cols, rowBound_t- R_BIAS), RED, 2);
	line(frame, Point(0, rowBound_b), Point(frame.cols, rowBound_b), RED, 2);
	line(frame, Point(0, rowBound_m), Point(frame.cols, rowBound_m), RED, 1);
	line(frame, Point(colBound, 0), Point(colBound, frame.rows), RED, 2);
	line(frame, Point(colBound_m, 0), Point(colBound_m, frame.rows), RED, 1);
	line(frame, Point(colBound_r, 0), Point(colBound_r, frame.rows), RED, 1);
	line(frame, Point(colBound_l, 0), Point(colBound_l, frame.rows), RED, 1);
	int temp = colBound + 500;
	//cout << temp << ", " << rowBound_b<< endl;
	//cout << contours.size() << endl;
	//line(frame, Point(temp, 0), Point(temp, frame.rows), RED, 2);

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
		//1
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
			//if (true){//Rect_area<2800 && ratio<4) {

			//	//drawContours(frame, contours, i, Scalar(0, 255, 255), 1, 8, hierarchy, 0, Point());
			//	rectangle(frame, contours_tl, contours_br, RED, 1, 8, 0);

			//	//  Include only suitable rectangles.
			//	refinery_count += 1;
			//	boundRect2[refinery_count] = boundRect[i];
			//}
		}
	}


	//for (int i = 1; i < contours.size(); i++) {

	//	ratio = (double)boundRect[i].width / boundRect[i].height;

	//	//  Filtering rectangles height/width ratio, and size.
	//	if (boundRect[i].tl().y > rowBound_t && boundRect[i].tl().x > colBound &&boundRect[i].tl().y < rowBound_b&& boundRect[i].width > boundRect[i].height)
	//	{
	//		if (true) {

	//			//drawContours(frame, contours, i, Scalar(0, 255, 255), 1, 8, hierarchy, 0, Point());
	//			rectangle(frame, boundRect[i].tl(), boundRect[i].br(), RED, 1, 8, 0);

	//			//  Include only suitable rectangles.
	//			refinery_count += 1;
	//			boundRect2[refinery_count] = boundRect[i];
	//		}
	//	}
	//}


	//boundRect2.resize(refinery_count);  //  Resize refinery rectangle array.

	/*sort(boundRect2.begin(), boundRect2.end(), [](Rect &rect1, Rect &rect2) {
		return rect1.tl().x < rect2.tl().x; }
	);
*/
}
void MyVideo::Brightness(int n)
{
	frame = frame + Scalar(n, n, n);
}
void MyVideo::histEqual()
{
	vector<Mat> ch(frame.channels());
	split(frame, ch);
	equalizeHist(ch[1], ch[1]);
	merge(ch, frame);
}

