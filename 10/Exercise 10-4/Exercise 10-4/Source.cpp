#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int atoi(const char* a[])
{
	istringstream iss{ *a };
	int i = 0;
	if (iss >> i)
		return i;
	throw runtime_error("not able to covert to int");
}

int main()
try {
	char a[] = "123";
	int i = atoi(&a[0]);
	cout << i;
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