#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <tuple>
#include <numeric>
using namespace std;

template <typename Cont, typename T>
T mean(Cont c)
{
	return accumulate(c.begin(), c.end(), T{}) / c.size();
}

template <typename Cont, typename T>
T median(Cont c)
{
	return (c.size() % 2) ? (c[c.size() / 2] + c[c.size() / 2 + 1]) / 2 : c[c.size() / 2 + 1];
}

int main()
{
	map<string, vector<double>> data;
	string s;
	double d;
	while (cin >> s >> d)
		data[s].push_back(d);

	list<tuple<string, double, double, double>> lst;
	for (auto x : data)
		lst.emplace_back(x.first,
			accumulate(x.second.begin(), x.second.end(), 0.0),
			mean<vector<double>, double>(x.second),
			median<vector<double>, double>(x.second)
		);
	for (auto x : lst)
		cout << get<0>(x) << ' ' << get<1>(x) << ' ' << get<2>(x) << ' ' << get<3>(x) << '\n';
}