#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
	map<string, pair<double, int>> values;

	for (pair<string, double> value; cin >> value.first >> value.second; )
	{
		values[value.first].first += value.second;
		values[value.first].second++;
	}

	for (auto p = values.begin(); p != values.end(); p++)
	{
		cout << p->first << ":\n"
			<< "sum: " << p->second.first << '\n'
			<< "mean: " << p->second.first / p->second.second << '\n';
	}
}