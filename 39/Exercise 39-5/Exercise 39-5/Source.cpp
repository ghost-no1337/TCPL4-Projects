#include "Chrono.h"
using namespace Chrono;

template <typename T>
void read_value(T& object, const string& prompt)
{
	cout << "Please enter " << prompt << ":\n";
	cin >> object;
}

int main()
{
	int i;
	read_value(i, "integer");
	cout << i << '\n';
	double d;
	read_value(d, "floating-point number");
	cout << d << '\n';
	string fname;
	read_value(fname, "file name");
	cout << fname << '\n';
	string maddr;
	read_value(maddr, "mail address");
	cout << maddr << '\n';
	Date dt;
	read_value(dt, "date");
	cout << dt;
}