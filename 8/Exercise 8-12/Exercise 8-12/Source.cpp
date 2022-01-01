#include <iostream>
#include <string>
#include <sstream>
#include <exception>
using namespace std;

int count_occourence(const string& s, const string& target)
{
	int count = 0;
	istringstream iss{ s };
	if (target.size() != 2)
		throw runtime_error("target size is not 2");

	for (char ch; iss >> ch; )
		if (ch == target[0]) {
			iss >> ch;
			if (ch == target[1])
				++count;
		}
	return count;
}

int count_occourence(char* cs[], char* ctarget[])
{
	string s = *cs;
	string target = *ctarget;

	return count_occourence(s, target);
}

int main()
try {
	string s = "xabaacbaxabb";
	string target = "ab";
	cout << count_occourence(s, target);
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	char ch; cin >> ch;
	return 1;
}
catch (...) {
	cerr << "error: unknown error\n";
	char ch; cin >> ch;
	return -1;
}