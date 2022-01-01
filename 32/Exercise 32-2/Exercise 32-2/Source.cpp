#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	vector<string> fruits;
	for (string s; cin >> s; )
		fruits.push_back(s);
	sort(fruits.begin(), fruits.end());
	for_each(fruits.begin(), fruits.end(), [](const string& s) {cout << s; });

	for (string& s : fruits)
		if (s[0] == 'a')
			cout << s << '\n';

	for (auto p = fruits.begin(); p != fruits.end(); ++p)
		if (*p == "citrus")
			fruits.erase(p);
	for_each(fruits.begin(), fruits.end(), [](const string& s) {cout << s; });
}