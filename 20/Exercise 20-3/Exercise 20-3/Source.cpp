#include "String.h"

int main()
try {
	String s = "Hello, World!";
	cout << s(0, 5) << '\n'
		<< s(7, 12) << '\n';
	s(0, 5) = "World";
	s(7, 12) = "Hello";
	cout << s;
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