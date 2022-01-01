#include <iostream>
using namespace std;

struct Date
{
    int year;
    int month;
    int day;

	Date(int y, int m, int d);
	Date();
};

const Date& default_date()
{
	static Date dd{ 1970, 1, 1 };
	return dd;
}

Date::Date()
	:year{ default_date().year },
	month{ default_date().month },
	day{ default_date().day } { }

Date::Date(int y, int m, int d)
	:year{ y }, month{ m }, day{ d } { }

ostream &operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year
              << ',' << d.month
              << ',' << d.day << ')';
}

istream &operator>>(istream& is, Date& dd)
{
    int y, m, d;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
    if (!is)
        return is;
    if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') {
        is.clear(ios_base::failbit);
        return is;
    }

	dd = Date{ y, m, d };
    return is;
}

int main()
{
    Date d;
    cin >> d;
    cout << d << '\n';
}