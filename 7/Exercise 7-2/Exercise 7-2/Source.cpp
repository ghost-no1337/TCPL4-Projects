#include <iostream>
using namespace std;

int main()
{
	char ch = 0xff;
	if (static_cast<int>(ch) < 0)
		cout << "signed";
	else
		cout << "unsigned";
}