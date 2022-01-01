#include "Chrono.h"
using namespace Chrono;

Date get_time(int i1, Month m, int i2) 
{
	if (m < Month::jan || m > Month::dec || 
		i1 > days_in_month(m, false) && i2 > days_in_month(m, false) ||
		i1 <= 0 && i2 <= 0 )
		throw Date::Bad_date();

	if (i1 > days_in_month(m, false) || i1 <= 0)
		return Date{ i2, m, i1 };
	else
		return Date{ i1, m, i2 };
}

int main()
{
	int i1 = 0, i2 = 0, i3 = 0;
	while (cin >> i1 >> i2 >> i3)
	try {
		cout << get_time(i1, static_cast<Month>(i2), i3) << '\n';
	}
	catch (Date::Bad_date) {
		cerr << "error: invalid date\n";
	}
}