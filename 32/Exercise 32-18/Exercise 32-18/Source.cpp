#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
	string iname;
	cin >> iname;
	ifstream ifs{ iname };
	if (!cin)
		throw runtime_error("cannot open file");
	
	set<string> words;

	for (string s; cin >> s; )
		words.insert(s);

	for_each(words.begin(), words.end(), [](const string& s) { cout << s << '\n'; });
}