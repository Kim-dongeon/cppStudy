#include "MyContrastClass.h"

using namespace cv;
using namespace std;

void trackBarChanged(int value, void *param)
{
	MyContrastClass *mcc = new MyContrastClass((Mat*)param);
	imshow("MyImage", mcc->getContrastedImage(value));
	delete(mcc);
}

int main(int argc, char** argv)
{
	Mat image = imread("C:/Users/KimDongUn/Desktop/°´Ã¼/glasses.jpg", IMREAD_UNCHANGED);
	int initialValue = 100;
	imshow("MyImage", image);

	createTrackbar("MyTrackbar", "MyImage", &initialValue, 200, trackBarChanged, &image);
	waitKey(0);
	return 0;
}

