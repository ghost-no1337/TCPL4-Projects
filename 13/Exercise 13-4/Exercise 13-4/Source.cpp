#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

runtime_error file_error(string prompt, string file_name)
{
	ostringstream oss;
	oss << prompt << file_name;
	return runtime_error(oss.str());
}

void output_file(string name)
{
	ifstream ifs{ name };
	if (!ifs)
		throw file_error("cannot open file: ", name);

	cout << "File " << name << ": \n";
	for (char ch; ifs.get(ch); )
		cout << ch;
	cout << '\n';
}

int main()
try {
	string line;
	getline(cin, line);

	istringstream iss{ line };
	vector<string> files;
	for (string s; iss >> s; )
		files.push_back(s);

	for (string& s : files)
		output_file(s);
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