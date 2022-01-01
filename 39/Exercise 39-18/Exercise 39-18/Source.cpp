#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class based {
public:
	friend ostream& operator<<(ostream& os, const based& b);
	based(int b, int v)
		:base{ b }, value{ v } { }
private:
	int base;
	int value;
};

char convert(int i) {
	if (i < 10)
		return i + '0';
	else if (10 <= i && i < 36)
		return i - 10 + 'A';
	else
		throw runtime_error{ "int not convertable" };
}

ostream& operator<<(ostream& os, const based& b)
{
	ostringstream oss;
	for (int v = b.value; v != 0; v /= b.base)
		oss << convert(v % b.base);
	string out = oss.str();
	reverse(out.begin(), out.end());
	return os << out;
}

int main()
{
	int b = 0, val = 0;
	while (cin >> b >> val)
	try {
		cout << based(b, val) << '\n';
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
}