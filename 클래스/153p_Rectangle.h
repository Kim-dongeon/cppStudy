#ifndef __153P_RECTANGLE_H_
#define __153P_RECTANGLE_H_

#include "153p_Point.h"

class Rectangle
{
private:
	Point upLeft;
	Point lowRight;

public:
	bool InitMembers(const Point &ul, const Point &lr);
	void ShowRecInfo() const;

};
#endif


