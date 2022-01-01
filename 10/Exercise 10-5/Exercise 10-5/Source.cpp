#include <iostream>
#include <string>
#include <sstream>
using namespace std;

char* itoa_t(int i, char b[], int length)
{
	ostringstream oss;
	oss << i;
	string s = oss.str();
	if (length < s.size())
		throw runtime_error("no enough buffer");
	for (int i = 0; i < s.size(); i++)
		b[i] = s[i];
	return b;
}

int main()
try {
	int i = 123;
	char b[10] = "";
	itoa_t(i, b, 10);
	cout << b;
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	char ch; cin >> ch;
	return 1;
}
catch (...) {
	cerr << "error: unknown error\n";
	char ch; cin >> ch;
	return -1;
}