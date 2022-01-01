#include <iostream>
using namespace std;

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

Month& operator++(Month &m);

class Date {
public:
	class Invalid { };
	Date(int y, Month m, int d);
	Date();

	int day() const { return d; }
	Month month() const { return m; }
	int year() const { return y; }

	void add_day(int n);
	void add_month(int n);
	void add_year(int n);
private:
	int y;
	Month m;
	int d;
};
bool is_date(int y, Month m, int d);
bool leapyear(int y);

int days_in_month(Month m, bool is_leapyear);

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);

Date::Date(int yy, Month mm, int dd)
	: y{ yy }, m{ mm }, d{ dd }
{
	if (!is_date(yy, mm, dd))
		throw Invalid{};
}

const Date& default_date()
{
	static Date dd{ 1970, Month::jan, 1 };
	return dd;
}

Date::Date()
	:y{ default_date().year() },
	m{ default_date().month() },
	d{ default_date().day() }
{
}

void Date::add_day(int n)
{
	if (n < 0)
		throw runtime_error("negative day");
	d += n;
	while (days_in_month(m, leapyear(y)) < d) {
		if (m == Month::dec) {
			d -= days_in_month(m, leapyear(y));
			++m;
			++y;
		}
		else {
			d -= days_in_month(m, leapyear(y));
			++m;
		}
	}
}

void Date::add_month(int n)
{
	if (n < 0)
		throw runtime_error("negative month");
	while (n >= 12) {
		++y;
		n -= 12;
	}
	while (n > 0) {
		if (m == Month::dec) {
			--n;
			++m;
			++y;
		}
		else {
			--n;
			++m;
		}
	}
	if (days_in_month(m, leapyear(y)) < d) {
		if (m == Month::dec) {
			d -= days_in_month(m, leapyear(y));
			++m;
			++y;
		}
		else {
			d -= days_in_month(m, leapyear(y));
			++m;
		}
	}
}

void Date::add_year(int n)
{
	if (m == Month::feb && d == 29 && !leapyear(y + n)) {
		m = Month::mar;
		d = 1;
	}
	y += n;
}

bool is_date(int y, Month m, int d)
{
	if (d <= 0)
		return false;
	if (m < Month::jan || Month::dec < m)
		return false;

	if (days_in_month(m, leapyear(y)) < d)
		return false;

	return true;
}

bool leapyear(int y)
{
	if (y % 100 == 0 && y % 400 != 0)
		return false;
	if (y % 4 == 0) {
		return true;
	}
	return false;
}

int days_in_month(Month m, bool is_leapyear)
{
	switch (m) {
	case Month::feb:
		return (is_leapyear) ? 29 : 28;
		break;
	case Month::apr: case Month::jun: case Month::sep: case Month::nov:
		return 30;
		break;
	default:
		return 31;
		break;
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
	return os << '(' << d.year()
		<< ',' << int(d.month())
		<< ',' << d.day() << ')';
}

istream& operator >> (istream& is, Date& dd)
{
	int y, m, d;
	char ch1, ch2, ch3, ch4;
	is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
	if (!is) return is;
	if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') {
		is.clear(ios_base::failbit);
		return is;
	}

	dd = Date(y, Month(m), d);

	return is;
}

Month& operator++(Month &m)
{
	m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
	return m;
}

enum class Day {
	sunday, monday, tuesday, wednesday, thursday, friday, saturday
};

int days_since_origin(const Date& d)
{
	const Date origin = default_date();
	int days = 0;

	if (d.year() < 1970)
		throw runtime_error("the date is before origin");

	for (int i = origin.year(); i < d.year(); ++i)
		days += (leapyear(i)) ? 366 : 365;
	for (int i = 1; i < int(d.month()); ++i)
		days += days_in_month(static_cast<Month>(i), leapyear(d.year()));
	days += d.day() - 1;

	return days;
}

int days_since_jan1(const Date& d)
{
	int days = 0;

	for (int i = 1; i < int(d.month()); ++i)
		days += days_in_month(static_cast<Month>(i), leapyear(d.year()));
	days += d.day() - 1;

	return days;
}

Day day_of_week(const Date& d)
{
	return static_cast<Day>((days_since_origin(d) + 4) % 7);
}

Date next_Monday(const Date& d)
{
	Date temp = d;
	temp.add_day(1);
	while (day_of_week(temp) != Day::monday)
		temp.add_day(1);
	return temp;
}

int main()
try {
	Date d;
	cin >> d;
	cout << d << '\n';
	d.add_day(1);
	d.add_month(1);
	d.add_year(1);
	cout << d << '\n'
		<< int(day_of_week(d)) << '\n'
		<< next_Monday(d) << '\n';
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