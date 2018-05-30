#include "MyVideo.hpp"

int main()
{
	MyVideo *myV = new MyVideo("C:/Users/KimDongUn/Desktop/°´Ã¼/blackbox_video1.mp4");
	int cnt = 0;
	while (1)
	{	
		myV->capToFrame();
	//	myV->getVideoSize();
	
		//myV->Brightness(50);
		if (myV->isFrameEmpty() == true) break;
		cnt++;
		cout << "Frame : " << cnt << endl;		
		
		myV->frame2Bin();
	//	myV->topHat(myV->getFrameB());
		myV->imageProcessing();
		myV->divideBlock();
		//myV->drawBolck();
		//myV->drawRectangle(myV->getFrame(),myV->getWidth(), myV->getHeight(), 30, 30, RED, 4);
		myV->detect();
		imshow("Frame",myV->getFrame());
		
		char c = (char)waitKey(0);
		if (c == 27) break;
	}
	delete myV;
	return 0;
}