#include "MyROI.h"

void onMouse(int event, int x, int y, int flags, void* userdata);

int main(int argc, char** argv)
{	
	MyROI *m = new MyROI("C:/Users/KimDongUn/Desktop/°´Ã¼/glasses.jpg");
	imshow("MouseEvent1", m->getImg());
	setMouseCallback("MouseEvent1", onMouse, m);

	waitKey(0);
	return 0;
}

void onMouse(int event, int x, int y, int flags, void *param)
{	
	MyROI *_m = (MyROI *)param;
	
	Mat roi;
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		_m->setFlag(true);
		_m->setTL(x, y);
		
		//cout << _m->getTL_x() << ", " << _m->getTL_y() << endl;
		break;
	case EVENT_LBUTTONUP:
		if (_m->getWidth() < 0)
		{
			_m->add_x(_m->width);
			_m->width *= -1;
		}
		if (_m->getHeight() < 0)
		{
			_m->add_y(_m->height);			
			_m->height *= -1;
		}
		//	printf("%d %d %d %d\n", tl_x, tl_y,width,height);
		cout << _m->getTL_x() << ", " << _m->getTL_y() << ", " << _m->getTL_x() + _m->getWidth() << ", " << _m->getTL_y() + _m->getHeight() << endl;
		rectangle(_m->getImg(), Point(_m->getTL_x(), _m->getTL_y()), Point(_m->getTL_x() + _m->getWidth(), _m->getTL_y() + _m->getHeight()), Scalar(255, 0, 0), 2);
		_m->rectOfImg(_m->getImg(), _m->getTL_x(), _m->getTL_y(), _m->width, _m->height);
		
		//cvtColor(roi, roi, COLOR_BGR2GRAY);
		//_m->frame2Gray();
		//_m->gray(_m->getProcessed(), _m->_gray);
		//	threshold(roi, roi, 128, 255, THRESH_OTSU);
		//Canny(_m->getProcessed(), _m->getProcessed(), 100, 200);
		//imshow("MouseEvent1", _m->getImg());
		imshow("Mouse", _m->getProcessed());
		//imshow("MouseEvent1", roi);
		_m->setFlag(false);
		break;
	case EVENT_MOUSEMOVE:
		if (_m->getFlag() ==true)
		{			
			_m->width = x - _m->getTL_x();
			_m->height = y - _m->getTL_y();
			printf("%d %d\n", _m->width, _m->height);
		}
		break;
	case EVENT_RBUTTONDOWN:

		break;
	default:
		break;

	}
}