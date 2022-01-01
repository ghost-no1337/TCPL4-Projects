#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace Chrono {
	enum class Month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

	class Date {
	public:
		class Bad_date { };

		explicit Date(int dd = { }, Month mm = { }, int yy = { });
		const Date& default_date();

		int day() const { return d; }
		Month month() const { return m; }
		int year() const { return y; }
		string string_rep() const;
		void char_rep(char s[], int max) const;

		Date& add_year(int n);
		Date& add_month(int n);
		Date& add_day(int n);
	private:
		Date(int dd, Month mm, int yy, int days)
			:d{ dd }, m{ mm }, y{ yy }, days_after_origin{ days } { }

		bool is_valid();
		void update(bool rep);

		int d;
		Month m;
		int y;
		int days_after_origin;
	};

	bool is_date(int d, Month m, int y);
	bool is_leapyear(int y);
	int days_in_month(Month m, bool is_leapyear);

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);

	ostream& operator<<(ostream& os, const Date& d);
	istream& operator>>(istream& is, Date& d);
	Month& operator++(Month &m);
}