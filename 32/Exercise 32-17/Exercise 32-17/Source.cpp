#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class phone_number {
public:
	phone_number(string s);
	phone_number& operator=(string s);
	phone_number(phone_number&) = default;
	phone_number& operator=(phone_number&) = default;

	string to_str() const;
private:
	string number;
};

phone_number::phone_number(string s)
{
	if (s.size() != 10)
		throw runtime_error("bad phone number length");

	number = s;
}

phone_number& phone_number::operator=(string s)
{
	if (s.size() != 10)
		throw runtime_error("bad phone number length");

	number = s;
	return *this;
}

string phone_number::to_str() const
{
	return number;
}

ostream& operator<<(ostream& os, const phone_number& p)
{
	return os << p.to_str();
}

istream& operator>>(istream& is, phone_number& p)
{
	string s;
	is >> s;
	p = s;
	return is;
}

int main()
try {
	phone_number microsoft_tel{ "4258828080" };
	cout << microsoft_tel << '\n';
	cin >> microsoft_tel;
	cout << microsoft_tel.to_str() << '\n';
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