#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
using namespace std;

bool is_comment_block = false;

bool is_comment(const string& s) {
	istringstream iss{ s };
	for (char ch; iss >> ch; ) {
		if (!is_comment_block) {
			if (ch == '/') {
				iss >> ch;
				if (ch == '/')
					return true;
				else if (ch == '*')
					is_comment_block = true;
			}
			else if (ch == '\"') {
				do {
					iss >> ch;
				} while (ch != '\"');
			}
		}
		else {
			if (ch == '*') {
				iss >> ch;
				if (ch == '/') {
					is_comment_block = false;
					return true;
				}
			}
		}
	}
	return is_comment_block;
}

string include(string s)
{
	regex include_pattern{ R"(#include ([\w."<>/]+))" };
	smatch matches;
	if (regex_search(s, matches, include_pattern))
		return matches[1];
	else
		return "";
}

int main()
try {
	string fname;
	cout << "Type the name of the input file: ";
	cin >> fname;
	ifstream ifs{ fname };
	if (!ifs)
		throw runtime_error("bad input filename");

	int comment_line = 0;
	int non_comment_line = 0;
	vector<string> includes;

	for (string line; getline(ifs, line); ) {
		if (is_comment(line))
			++comment_line;
		else
			++non_comment_line;

		if (include(line) != "")
			includes.push_back(include(line));
	}

	cout << "Comment line: " << comment_line << '\n'
		<< "Non-comment line: " << non_comment_line << '\n';
	if (includes.size()) {
		cout << "included files:\n";
		for (string& s : includes)
			cout << s;
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