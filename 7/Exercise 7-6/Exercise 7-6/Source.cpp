#include <iostream>
#include <string>
using namespace std;

template <typename T>
void print_size(const T& t, const string& s)
{
	cout << "The size of " << s << " is " << sizeof(t) << '\n';
}

int main()
{
	print_size(bool{}, "bool");
	print_size(char{}, "char");
	print_size(short{}, "short");
	print_size(int{}, "int");
	print_size(long{}, "long");
	print_size(long long{}, "long long");
	print_size(float{}, "float");
	print_size(double{}, "double");
	print_size(long double{}, "long double");
	print_size(unsigned{}, "unsigned");
	print_size(unsigned long{}, "unsigned long");
}