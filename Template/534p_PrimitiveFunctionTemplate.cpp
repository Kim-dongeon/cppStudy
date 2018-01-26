#include <iostream>
using namespace std;

template <class T1, class T2>
void ShowData(double num)
{
	cout << (T1)num << ", " << (T2)num << endl;
}
int main()
{
	ShowData<char, int>(65);
	ShowData<char, double>(65);
	ShowData<char, int>(65.7);
	ShowData<short, double>(65);
}
