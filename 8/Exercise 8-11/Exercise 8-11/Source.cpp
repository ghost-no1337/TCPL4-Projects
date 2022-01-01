#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<string> vs;
	for (string s; cin >> s && s != "Quit";)
		vs.push_back(s);
	sort(vs.begin(), vs.end());
	for (const string& s : vs)
		cout << s << '\n';
}