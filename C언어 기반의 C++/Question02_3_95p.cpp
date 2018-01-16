#include <iostream>
using namespace std;

typedef struct __Point
{
	int xpos;
	int ypos;
}Point;

Point& PntAdder(const Point &p1, const Point &p2)
{
	Point *sum = new Point;
	sum->xpos = p1.xpos + p2.xpos;
	sum->ypos = p1.ypos + p2.ypos;
	return *sum;

}
int main()
{
	Point *p1 = new Point;
	p1->xpos = 1;
	p1->ypos = 2;
	Point *p2 = new Point;
	p2->xpos = 3;
	p2->ypos = 4;
	

	Point sum = PntAdder(*p1, *p2);
	cout << sum.xpos << endl;
	cout << sum.ypos << endl;

	Point p3;
	p3.xpos = 0;
	p3.ypos = 1;
	Point _sum = PntAdder(p3,p3);
	cout << _sum.xpos << endl;
	cout << _sum.ypos << endl;
	delete(p1);
	delete(p2);
	

}