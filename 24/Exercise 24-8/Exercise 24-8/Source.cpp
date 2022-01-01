#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
struct Map {
	vector<pair<string, T>> vec;

	const T& operator[] (const string&) const;
	T& operator[](const string&);

	auto begin() { return vec.begin(); }
	auto end() { return vec.end(); }
};

template <typename T>
T& Map<T>::operator[](const string& s)
{
	for (auto& x : vec)
		if (s == x.first) 
			return x.second;

	vec.push_back({ s, {} });

	return vec.back().second;
}

template <typename T>
const T& Map<T>::operator[](const string& s) const
{
	for (auto& x : vec)
		if (s == x.first)
			return x.second;

	throw runtime_error("bad key");
}

int main()
{
	Map<int> values;
	string buf;
	while (cin >> buf)
		++values[buf];
	for (auto x : values)
		cout << '{' << x.first << ',' << x.second << "}\n";
}