#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x),ypos(y)
	{}
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
	Point& operator++()
	{
		xpos += 1;
		ypos += 1;
		return *this;
	}
	const Point operator++(int) const
	{
		const Point retobj(xpos, ypos); //const Point retobj(*this);
		xpos += 1;
		ypos += 1;
		return retobj;
	}
	friend Point& operator--(Point &ref);
	friend const Point operator--(Point &ref, int);
};

Point& operator--(Point &ref)
{
	ref.xpos -= 1;
	ref.ypos -= 1;
	return ref;
}
const Point operator--(Point &ref, int)
{
	const Point retObj(ref);
	ref.xpos -= 1;
	ref.ypos -= 1;
	return retObj;
}
int main()
{
	Point pos(1, 2);
	++pos;
	pos.ShowPosition();
	--pos;
	pos.ShowPosition();

	++(++pos);
	pos.ShowPosition();
	--(--pos);
	pos.ShowPosition();


	Point pos1(3, 5);
	Point cpy;
	cpy = pos1--;
	cpy.ShowPosition();
	pos1.ShowPosition();

	cpy = pos1++;
	cpy.ShowPosition();
	pos1.ShowPosition();
	return 0;
}