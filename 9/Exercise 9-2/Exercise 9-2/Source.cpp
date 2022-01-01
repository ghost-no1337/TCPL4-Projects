#include <iostream>
#include <string>
using namespace std;

struct Month {
	string month;
	int dates;
};

ostream& operator<<(ostream& os, const Month& m)
{
	return os << m.month << ": " << m.dates;
}

void print_months(string month[12], int dates[12])
{
	for (int i = 0; i < 12; i++)
		cout << month[i] << ": " << dates[i] << '\n';
}

int main()
{
	string months[12] = { "January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December" };
	int dates[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	print_months(months, dates);

	Month table[12] = { Month{ "January", 31 }, Month{ "February", 28 }, Month{ "March", 30 }, Month{ "April", 30 },
		Month{ "May", 31 }, Month{ "June", 30 }, Month { "July", 31 }, Month{ "August", 31 },
		Month{ "September", 30 }, Month{ "October", 31 }, Month{ "November", 30 }, Month{ "December", 31 } };
	for (int i = 0; i < 12; i++)
		cout << table[i] << '\n';
}