#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

void draw_houghLines(Mat src, Mat& dst, vector<Vec2f> lines, int nline, vector<Point> dot)
{
	cvtColor(src, dst, CV_GRAY2BGR);
	for (int i = 0; i < (int)lines.size(); i++)
	{
		float rho = lines[i][0];
		float theta = lines[i][1];
		double a = cos(theta);
		double b = sin(theta);
		//-----------------------------------------------------------
		vector<Point>::iterator it;
		for (it = dot.begin(); it != dot.end(); ++it)
		{
			if (abs(it->x * cos(theta) + it->y * sin(theta) - rho) < 2)
			{
				dst.at<Vec3b>(it->x, it->y) = Vec3b(0, 0, 255);
			}
		}
		//------------------------------------------------------------
	//	Point2d pt(a*rho, b*rho);
		//Point2d delta(1000 * -b, 1000 * a);
		//line(dst, pt + delta, pt - delta, Scalar(0, 255, 0), 1, LINE_AA);
	}
}

void trackBarChanged(int value, void *param)
{
	Mat *canny = (Mat*)param;
	Mat dst;
	double rho = 1;
	double theta = CV_PI / 180;
	vector<Vec2f> lines;
	vector<Point> p;
	HoughLines(*canny, lines, rho, theta, value);
	draw_houghLines(*canny, dst, lines, 1000,p);

	//imshow("org", img);
	//imshow("canny", canny);
	imshow("hough", dst);
}
void findWhite(Mat &canny, vector<Point> &v)
{
	for (int i = 0; i < canny.size().height; i++)
	{
		for (int j = 0; j < canny.size().width; j++)
		{
			if ((double)canny.at<uchar>(i, j) == 255.0)
			{
				//canny.at<uchar>(i, j) = 0;
				v.push_back(Point(i, j));
			}
		}		
	}
}
int main(int argc, char** argv)
{	
	Mat img= imread("C:/Users/KimDongUn/Desktop/°´Ã¼/rec.PNG", IMREAD_UNCHANGED);

	Mat gray, canny, dst;
	double rho = 1;
	double theta = CV_PI / 180;
	cvtColor(img, gray, CV_BGR2GRAY);
	GaussianBlur(gray, canny, Size(5, 5), 2, 2);
	Canny(canny, canny, 100, 150, 3);


	vector<Point> dots;
	//---------------------------------------------------

	findWhite(canny, dots);

	//-----------------------------------------------------

	vector<Vec2f> lines;
	HoughLines(canny, lines, rho, theta, 30);
	draw_houghLines(canny, dst, lines, 1000,dots);

	//imshow("canny", canny);
	
	//imshow("org", img);
	//imshow("canny", canny);
	imshow("hough", dst);
	int initialValue = 100;
	//createTrackbar("MyTrackbar", "hough", &initialValue, 200, trackBarChanged, &canny);
	
	waitKey(0);
	return 0;
}

