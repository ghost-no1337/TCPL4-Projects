#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int stoi_t(const string& s)
{
	istringstream iss{ s };
	int i = 0;
	iss >> i;
	return i;
}

int main()
{
	for (string s; cin >> s; )
		cout << stoi_t(s) << '\n';
}
