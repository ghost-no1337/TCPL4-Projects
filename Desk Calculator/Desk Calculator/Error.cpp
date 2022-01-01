#include "dc.h"

namespace Error {
	int no_of_errors;
	double error(const string& s);
}

double Error::error(const string& s)
{
	no_of_errors++;
	cerr << "error: " << s << '\n';
	return 1;
}