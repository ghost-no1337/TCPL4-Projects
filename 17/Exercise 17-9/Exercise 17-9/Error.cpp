#include "Calculator.h"

double Error::error(const string& s)
{
	cerr << "error: " << s << '\n';
	return 1;
}