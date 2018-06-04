#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void* userdata);

bool flag = false;
int tl_x, tl_y, br_x, br_y;
int width, height;
int main(int argc, char** argv)
{
	
	Mat image = imread("C:/Users/KimDongUn/Desktop/°´Ã¼/glasses.jpg", IMREAD_UNCHANGED);
	
	imshow("MouseEvent1", image);
	setMouseCallback("MouseEvent1", onMouse,&image);

	waitKey(0);
	return 0;
}

void onMouse(int event, int x, int y, int flags, void *param)
{
	
	Mat _img = *(Mat *)param;
	
	Vec3b  bgr = 0;
	Mat roi;
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		flag = true;
		tl_x = x;
		tl_y = y;
		
		break;
	case EVENT_LBUTTONUP:		
		if (width < 0)
		{
			tl_x += width;
			width *= -1;
		}
		if (height < 0)
		{
			tl_y += height;
			height *= -1;
		}
	//	printf("%d %d %d %d\n", tl_x, tl_y,width,height);
		cout << tl_x << ", " << tl_y << ", " << tl_x + width << ", " << tl_y + height << endl;
		rectangle(_img, Point(tl_x, tl_y), Point(tl_x + width, tl_y + height), Scalar(255, 0, 0), 2);
		roi = _img(Rect(tl_x,tl_y, width,height));
		cvtColor(roi, roi, COLOR_BGR2GRAY);
	//	threshold(roi, roi, 128, 255, THRESH_OTSU);
		Canny(roi,roi, 100, 200);
		imshow("MouseEvent1", _img);
		imshow("MouseEven1", roi);
		flag = false;
		break;
	case EVENT_MOUSEMOVE:
		if (flag)
		{
			//printf("%d %d\n", tl_x, tl_y);
			width = x-tl_x ;
			height = y-tl_y ;
		}
		break;
	case EVENT_RBUTTONDOWN:
		
		break;
	default:
		break;

	}
}