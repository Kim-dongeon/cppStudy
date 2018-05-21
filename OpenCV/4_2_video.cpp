#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	VideoCapture cap("C:/Users/KimDongUn/Desktop/��ü/blackbox_video1.mp4");
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
		adaptiveThreshold(frame, binImg, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, 3.0);*/	//�ֺ��� �ȼ� ���� ��������� ���� 5=����� �� �̿��ȼ��� ����(25��),�ֺ��� ��պ��� 3.0���̰� ���� �ٲ��.
		//morphologyEx(binImg, openImg, MORPH_OPEN, kernel);

		cvtColor(frame, frame, COLOR_BGR2GRAY);//200�� �ȳ����� �ֺ��� edge�� ���� ��� �ּ� 100�̾�� edge�̴�. ���� �߽����� 200�̻� ���̰� ���� edge�̴�!
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