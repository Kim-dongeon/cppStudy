#include <iostream>
using namespace std;

void Plus(int &num)
{
	num++;
}
void change(int &num)
{
	num = -num;
}
int main()
{
	int num = 1;
	for (int i = 0; i < 10; i++)
	{
		Plus(num);
		change(num);
		cout << num << endl;
	}

}