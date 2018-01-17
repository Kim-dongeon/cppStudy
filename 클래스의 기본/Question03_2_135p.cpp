#include <iostream>
#include <cstring>
using namespace std;

class Printer
{
private:
	char name[20];
public:
	void SetString(char *str);
	void ShowString();
};

void Printer::SetString(char *str)
{
	strcpy(name, str);
}
void Printer::ShowString()
{
	printf("%s\n", name);
}
int main()
{
	Printer pnt;
	pnt.SetString("Hello World");
	pnt.ShowString();

	pnt.SetString("I Love C++");
	pnt.ShowString();
}