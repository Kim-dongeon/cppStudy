#include <iostream>
#include "153p_Point.h"
#include "153p_Rectangle.h"
using namespace std;

int main()
{
	Point pos1;
	if (!pos1.InitMembers(-2, 4))
	{
		cout << "�ʱ�ȭ ����" << endl;
	}
	if (!pos1.InitMembers(2, 4))
	{
		cout << "�ʱ�ȭ ����" << endl;
	}

	Point pos2;
	if (!pos2.InitMembers(5, 9))
	{
		cout << "�ʱ�ȭ ����" << endl;
	}

	Rectangle rec;
	if (!rec.InitMembers(pos2, pos1))
	{
		cout << "���簢�� �ʱ�ȭ ����" << endl;
	}
	rec.InitMembers(pos1, pos2);
	rec.ShowRecInfo();
	return 0;
}