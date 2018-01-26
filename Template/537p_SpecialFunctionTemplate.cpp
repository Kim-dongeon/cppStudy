#include <iostream>
#include <cstring>
using namespace std;

template <typename T>
T MAX(T a, T b)
{
	return a > b ?  a : b;
}

template <>
char* MAX(char *a, char *b)
{
	cout << "char* MAX<char*>(char*a,char*b)" << endl;
	return strlen(a) > strlen(b) ? a : b;
}

template <>
const char* MAX(const char* a, const char* b)
{
	return strcmp(a, b) > 0 ? a : b;
}

int main()
{
	cout << MAX(11, 15) << endl;;
	cout << MAX('T', 'Q') << endl;;
	cout << MAX(3.5, 6.5) << endl;;
	cout << MAX("Simple", "Best") << endl;

	char str1[] = "Simeple";
	char str2[] = "Best";
	cout << MAX(str1, str2) << endl;
	return 0;
}