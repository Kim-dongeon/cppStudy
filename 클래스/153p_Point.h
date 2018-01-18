#ifndef __153P_POINT_H_
#define __153P_POINT_H_

class Point
{
private:
	int x;
	int y;

public:
	bool InitMembers(int xpos, int ypos);
	int GetX() const;
	int GetY() const;
	bool SetX(int xpos);
	bool SetY(int ypos);
};

#endif