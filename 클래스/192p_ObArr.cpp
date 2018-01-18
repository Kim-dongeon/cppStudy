#include <iostream>
#include <cstring>
using namespace std;

class Person
{
private:
	char *name;
	int age;

public:
	/*Person(char *myname, int _age)
	{
		int len = strlen(myname) + 1;
		name = new char[len];
		strcpy(name, myname);
		age = _age;
	}*/
	Person()
	{
		name = NULL;
		age = 0;
		cout << "called Person()" << endl;
	}
	void SetPersonInfo(char *myname, int _age)
	{
		name = myname;
		age = _age;
	}
	void showPersonInfo() const
	{
		cout << "이름 : " << name << ",";
		cout << "나이 : " << age << endl;
	}
	~Person()
	{
		delete[]name;
		cout << "called destructor!" << endl;
	}	
};
int main()
{
	Person parr[3];
	char namestr[10];
	int age, len;
	char *strptr;

	for (int i = 0; i < 3; i++)
	{
		cout << "이름 : ";
		cin >> namestr;
		cout << "나이 : ";
		cin >> age;
		len = strlen(namestr)+1;
		strptr = new char[len];
		strcpy(strptr, namestr);
		parr[i].SetPersonInfo(strptr, age);
	}

	parr[0].showPersonInfo();
	parr[1].showPersonInfo();
	parr[2].showPersonInfo();
}