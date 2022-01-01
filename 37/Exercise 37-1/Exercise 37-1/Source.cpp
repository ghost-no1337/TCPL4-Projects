#include <iostream>
#include <string>
using namespace std;

string concatenation(const string& s1, const string& s2)
{
	return s1 + "." + s2;
}

int main()
{
	for (string s1, s2; cin >> s1 >> s2; )
		cout << concatenation(s1, s2) << '\n';
}