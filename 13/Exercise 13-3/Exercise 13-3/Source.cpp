#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	string line;
	getline(cin, line);

	istringstream iss{ line };
	vector<string> names;
	for (string s; iss >> s; )
		names.push_back(s);

	for (string& s : names)
		cout << "Hello, " << s << "!\n";
}