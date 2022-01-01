#include "Chrono.h"
using namespace Chrono;

int main()
try {
	Date d;
	cin >> d;
	cout << d << '\n';
	d.add_day(1);
	d.add_month(1);
	d.add_year(1);
	cout << d << '\n';
}
catch (Date::Bad_date) {
	cerr << "error: bad date\n";
	char ch; cin >> ch;
	return 2;
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