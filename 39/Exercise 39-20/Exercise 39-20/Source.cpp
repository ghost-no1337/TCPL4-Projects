#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Form;

struct Bound_form {
	const Form& f;
	double val;
};

class Form {
	friend ostream& operator<<(ostream&, const Bound_form&);
	int prc;
	int wdt;
	int fmt;
public:
	explicit Form(int p = 6, ios_base::fmtflags f = 0, int w = 0) : prc{ p }, fmt{ f }, wdt{ w } {}
	Bound_form Form::operator()(double d) const
	{
		return Bound_form{ *this,d };
	}
	Form& scientific() { fmt = ios_base::scientific; return *this; }
	Form& fixed() { fmt = ios_base::fixed; return *this; }
	Form& general() { fmt = 0; return *this; }
	Form& uppercase();
	Form& lowercase();
	Form& precision(int p) { prc = p; return *this; }
	Form& width(int w) { wdt = w; return *this; }
	Form& fill(char);
	Form& plus(bool b = true);
	Form& trailing_zeros(bool b = true);
};

ostream& operator<<(ostream& os, const Bound_form& bf)
{
	ostringstream s;
	s.precision(bf.f.prc);
	s.setf(bf.f.fmt, ios_base::floatfield);
	s << bf.val;
	return os << s.str();
}

Form gen4 {4};
void f(double d)
{
	Form sci8;
	sci8.scientific().precision(8);
	cout << d << ' ' << gen4(d) << ' ' << sci8(d) << ' ' << d << '\n';
	Form sci{ 10, ios_base::scientific };
	cout << d << ' ' << gen4(d) << ' ' << sci(d) << ' ' << d << '\n';
}

int main()
{
	f(1234.56789);
}