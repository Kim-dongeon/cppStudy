#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	VideoCapture cap("C:/Users/KimDongUn/Desktop/객체/blackbox_video1.mp4");
	if (!cap.isOpened())
	{
		cout << "Error!!" << endl;
		return -1;
	}
	int cnt = 0;
	while (1)
	{
		Mat frame;
		cap >> frame;
		cnt++;
		if (frame.empty())
		{
			break;
		}
		Mat binImg,openImg;
		Mat kernel(3, 3, CV_8U);
		/*cvtColor(frame, frame, COLOR_BGR2GRAY);
		adaptiveThreshold(frame, binImg, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, 3.0);*/	//주변의 픽셀 값과 가중평균을 내서 5=평균을 낼 이웃픽셀의 개수(25개),주변과 평균보다 3.0차이가 나면 바뀐다.
		//morphologyEx(binImg, openImg, MORPH_OPEN, kernel);

		cvtColor(frame, frame, COLOR_BGR2GRAY);//200은 안넘지만 주변에 edge가 있을 경우 최소 100이어야 edge이다. 나를 중심으로 200이상 차이가 나면 edge이다!
		Canny(frame, frame, 100, 200);
		adaptiveThreshold(frame, binImg, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 3.0);
		morphologyEx(binImg, openImg, MORPH_OPEN, kernel);
		imshow("Frame", openImg);
		char c = (char)waitKey(1);
		if (c == 27) break;
		cout << cnt << endl;
	}
	
	cap.release();
	destroyAllWindows();
	
	return 0;
}