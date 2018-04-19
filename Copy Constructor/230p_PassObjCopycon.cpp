#include <iostream>

using namespace std;

class SoSimple
{
private:
	int num;
public:
	SoSimple(int n) : num(n) {		}
	SoSimple(const SoSimple& copy) :num(copy.num)
	{
		cout << "Called SoSimple(const SoSimple& copy)" << endl;
	}
	void showData()
	{
		cout << "num : " << num << endl;
	}
};
void SimpleFunc(SoSimple ob)
{
	ob.showData();
}
int main()
{
	SoSimple obj(7);
	cout << "�Լ� ȣ�� ��" << endl;
	SimpleFunc(obj);
	cout << "�Լ� ȣ�� ��" << endl;
}