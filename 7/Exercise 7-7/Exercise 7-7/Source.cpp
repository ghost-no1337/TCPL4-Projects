#include <iostream>
#include <string>
using namespace std;

void print_char(const char& ch)
{
	cout << "The value of \"" << ch << "\" is " << hex << static_cast<int>(ch) << '\n';
}

int main()
{
	for (char ch = 'a'; ch <= 'z'; ch++)
		print_char(ch);
	for (char ch = '0'; ch <= '9'; ch++)
		print_char(ch);
}