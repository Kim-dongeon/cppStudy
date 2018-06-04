#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void* userdata);

int main(int argc, char** argv)
{
	Mat image = imread("C:/Users/KimDongUn/Desktop/°´Ã¼/glasses.jpg", IMREAD_UNCHANGED);
	//image.setTo(Scalar(255,255,255));

	imshow("MouseEvent1", image);
	setMouseCallback("MouseEvent1", onMouse, &image);
	waitKey(0);
	return 0;
}

void onMouse(int event, int x, int y, int flags, void *param)
{
	Mat *_img = (Mat *)param;
	Vec3b  bgr = 0;
	Mat roi;
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		cout << "Left Button Click" << " x" << x << ", y" << y << ")" << endl;
		circle(*_img, Point(x, y), 10, Scalar(0, 0, 255), 2);
		imshow("MouseEvent1", *_img);
		break;
	case EVENT_RBUTTONDOWN:
		cout << "right Botton Click" << " x" << x << ", y" << y << ")" << endl;
		break;
	default:
		break;

	}
}