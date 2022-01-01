#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <set>
#include "Chrono.h"
using namespace std;
using namespace Chrono;

Date to_date(string s) 
{
	regex date{ R"(\d{2}/\d{2}/\d{4})" };
	smatch matches;
	if (regex_match(s, matches, date)) {
		istringstream iss{ s };
		Date dd;
		int d, m, y;
		char ch1, ch2;
		iss >> m >> ch1 >> d >> ch2 >> y;

		dd = Date{ d, static_cast<Month>(m), y };
		return dd;
	}
	throw runtime_error("invalid date");
}

template <>
class std::less<Date> {
public:
	bool operator()(Date d1, Date d2)
	{
		if (d1.year() == d2.year()) {
			if (d1.month() == d2.month())
				return d1.day() < d2.day();
			return d1.month() < d2.month();
		}
		return d1.year() < d2.year();
	}
};

int main()
try {
	regex date_pat{ R"(\d{2}/\d{2}/\d{4})" };
	set<Date> dates;

	for (string s; getline(cin, s); )
		dates.insert(to_date(s));

	for_each(dates.begin(), dates.end(), [](const Date& d) { cout << d << '\n'; });
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