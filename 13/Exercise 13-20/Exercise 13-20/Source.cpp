#include <iostream>
using namespace std;

int factorial(int i)
{
	if (i <= 0)
		throw runtime_error("cannot calculate factorial for negative numbers");
	int result = 1;
	for (; i != 1; i--) {
		result *= i;
	}
	return result;
}

int main()
try {
	int i = 0;
	cin >> i;
	cout << factorial(i);
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