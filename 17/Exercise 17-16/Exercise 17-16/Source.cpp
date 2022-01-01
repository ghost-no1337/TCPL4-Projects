#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

map<string, vector<int>>& find_words(istream& is, const vector<string>& vs)
{
	map<string, vector<int>> results;

	int lineno = 1;
	for (string line; getline(is, line); lineno++) {
		istringstream iss{ line };
		for (string word; iss >> word; )
			for (int i = 0; i < vs.size(); i++)
				if (vs[i] == word)
					results[vs[i]].push_back(lineno);
	}

	return results;
}

int main()
try {
	string iname;
	cout << "Enter input file name: ";
	cin >> iname;
	ifstream ifs{ iname };
	if (!ifs)
		throw runtime_error("cannot open file");

	vector<string> keywords;
	cout << "Enter the words to search:\n";
	for (string s; cin >> s; )
		keywords.push_back(s);

	map<string, vector<int>> result = find_words(ifs, keywords);
	for (auto x : result) {
		cout << x.first << " line numbers: ";
		for (int i = 0; i < x.second.size(); i++)
			cout << x.second[i] << ' ';
	}
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