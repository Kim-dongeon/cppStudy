#include <iostream>
using namespace std;

class AAA
{
private:
	int num1;
public:
	virtual void Func1() { cout << "Func1" << endl; }
	virtual void Func2() { cout << "Func2" << endl; }
	virtual void Func3() {}

	/*void Func1() { cout << "Func1" << endl; }
	void Func2() { cout << "Func2" << endl; }*/
};

class BBB : public AAA
{
private :
	int num2;
public:
	virtual void Func1() { cout << "BBB::Fun1" << endl; }
	//void Func1() { cout << "BBB::Fun1" << endl; }
	void Func3() { cout << "Func3" << endl; }
};

int main()
{
	AAA *aptr = new AAA();
	aptr->Func1();
	aptr->Func2();
	cout << "---------------------" << endl;
	BBB * bptr = new BBB();
	bptr->Func1();
	bptr->Func2();
	bptr->Func3();
	cout << "------------------------" << endl;
	AAA *Abptr = new BBB();
	Abptr->Func1();
	Abptr->Func2();
	Abptr->Func3();
	
	
}
