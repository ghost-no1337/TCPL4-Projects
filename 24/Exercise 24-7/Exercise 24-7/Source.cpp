#include <iostream>
#include <string>
#include <map>
using namespace std;

template <typename T, typename U>
pair<T, U> get_value()
{
	T t;
	U u;
	cin >> t;
	while (!(cin >> u)) {
		cin.clear();
		T temp;
		cin >> temp;
		t += ' ' + temp;
	}
	return make_pair(t, u);
}

int main()
{
	map<string, double> values;
	pair<string, double> val;
	while (true) {
		val = get_value<string, double>();
		if (val.first != "quit")
			values[val.first] += val.second;
		else break;
	}
	for (auto x : values)
		cout << x.first << ' ' << x.second << '\n';
}