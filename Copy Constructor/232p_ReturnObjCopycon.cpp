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
	SoSimple& AddNum(int n)
	{
		num += n;
		return *this;
	}
};
SoSimple SimpleFunc(SoSimple ob)
{
	cout << "return ÀÌÀü" << endl;
	return ob;
}
int main()
{
	SoSimple obj(7);
	SimpleFunc(obj).AddNum(30).showData();
	obj.showData();
}