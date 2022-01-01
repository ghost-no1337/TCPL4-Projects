#include "Chrono.h"

namespace Chrono {
	Date::Date(int dd, Month mm, int yy)
		:d{ dd }, m{ mm }, y{ yy }
	{
		if (y == 0) y = default_date().year();
		if (m == Month{}) m = default_date().month();
		if (d == 0) d = default_date().day();

		if (!is_valid())
			throw Bad_date{};
		update(false);
	}

	const Date& Date::default_date()
	{
		static Date dd{ 1, Month::jan, 1970, 0 };
		return dd;
	}

	string Date::string_rep() const
	{
		ostringstream oss;
		oss << static_cast<int>(m) << '/' << d << '/' << y;
		return oss.str();
	}

	void Date::char_rep(char s[], int max) const
	{
		string rep = string_rep();
		if (rep.size() > max)
			return;
		s = const_cast<char*>(rep.c_str());
	}

	Date& Date::add_day(int n)
	{
		days_after_origin += n;
		update(true);
		return *this;
	}

	Date& Date::add_month(int n)
	{
		add_year(n / 12);
		n %= 12;
		if (n > 0)
			while (n > 0) {
				days_after_origin += days_in_month(m, is_leapyear(y));
				update(true);
				--n;
			}
		else {
			while (n < 0) {
				days_after_origin -= days_in_month(m, is_leapyear(y));
				update(true);
				++n;
			}
		}
		
		return *this;
	}

	Date& Date::add_year(int n)
	{
		y += n;
		update(false);
		return *this;
	}

	bool Date::is_valid()
	{
		return (is_date(d, m, y) && y >= 1970);
	}

	void Date::update(bool rep)
	{
		if (rep) {
			if (days_after_origin < 0)
				throw Bad_date{};
			d = default_date().day();
			m = default_date().month();
			y = default_date().year();

			int days = days_after_origin;
			while (days > ((is_leapyear(y)) ? 366 : 365)) {
				days -= (is_leapyear(y)) ? 366 : 365;
				++y;
			}
			while (days > days_in_month(m, is_leapyear(y))) {
				days -= days_in_month(m, is_leapyear(y));
				++m;
			}
			d = days + 1;
		}
		else {
			if (y < default_date().year())
				throw Bad_date{};
			days_after_origin = 0;
			for (int i = default_date().year(); i < y; ++i)
				days_after_origin += (is_leapyear(i)) ? 366 : 365;
			for (int i = static_cast<int>(default_date().month()); i < static_cast<int>(m); ++i)
				days_after_origin += days_in_month(static_cast<Month>(i), is_leapyear(y));
			days_after_origin += d - 1;
		}
	}

	bool is_date(int d, Month m, int y)
	{
		if (d <= 0)
			return false;
		if (m < Month::jan || Month::dec < m)
			return false;
		if (days_in_month(m, is_leapyear(y)) < d)
			return false;

		return true;
	}

	bool is_leapyear(int y)
	{
		if (y % 100 == 0 && y % 400 != 0)
			return false;
		if (y % 4 == 0)
			return true;
		return false;
	}

	int days_in_month(Month m, bool is_leapyear)
	{
		switch (m) {
		case Month::feb:
			return (is_leapyear) ? 29 : 28;
		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			return 30;
		default:
			return 31;
		}
	}

	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.day()
			<< ',' << static_cast<int>(d.month())
			<< ',' << d.year() << ')';
	}

	istream& operator>>(istream& is, Date& dd)
	{
		int d, m, y;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> d >> ch2 >> m >> ch3 >> y >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') {
			is.clear(ios_base::failbit);
			return is;
		}

		dd = Date{ d, static_cast<Month>(m), y };

		return is;
	}

	Month& operator++(Month &m)
	{
		m = (m == Month::dec) ? Month::jan : static_cast<Month>(static_cast<int>(m) + 1);
		return m;
	}
}