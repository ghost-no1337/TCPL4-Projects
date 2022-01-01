#include <iostream>
#include <string>
#include <fstream>
#include <complex>
using namespace std;

int main()
{
	string iname;
	cin >> iname;
	ifstream ifs{ iname };
	if (!ifs)
		throw runtime_error{ "cannot open input file" };

	for (double d1, d2; ifs >> d1 >> d2; )
		cout << complex<double>{ d1, d2 };
}