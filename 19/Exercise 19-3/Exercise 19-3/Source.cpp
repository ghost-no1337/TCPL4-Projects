#include <iostream>
using namespace std;

class INT {
	int v;
public:
	INT(int i = 0)
		:v{ i } { }
	INT& operator=(int i) { v = i; return *this; }
	operator int() const { return v; }
};

int main()
{
	int i1 = 0, i2 = 0;
	cin >> i1 >> i2;
	INT I1 = i1;
	INT I2 = i2;
	cout << I1 + I2 << '\n'
		<< I1 - I2 << '\n'
		<< I1 * I2 << '\n'
		<< I1 / I2 << '\n';
}