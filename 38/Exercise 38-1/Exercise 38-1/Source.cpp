#include "Chrono.h"
#include <fstream>
#include <regex>
using namespace std;
using namespace Chrono;

string to_iso(string s) {
	regex date{ R"((\d{2})/(\d{2})/(\d{4}))" };
	smatch matches;
	if (regex_match(s, matches, date)) {
		if (is_date(stoi(matches[2]), static_cast<Month>(stoi(matches[1])), stoi(matches[3]))) {
			ostringstream oss;
			oss << matches[3] << '-' << matches[1] << '-' << matches[2];
			return oss.str();
		}
		else
			throw runtime_error("not a valid date");
	}
	else
		throw runtime_error{ "cannot find date in the string" };
}

int main()
try {
	string iname;
	cin >> iname;
	ifstream ifs{ iname };

	string oname;
	cin >> oname;
	ofstream ofs{ oname };
	regex line_pat{ R"(^([\w ]+)(\d{2}/\d{2}/\d{4})([\w ]+)$)" };

	for (string line; getline(ifs, line); ) 
	try {
		smatch matches;
		if (regex_match(line, matches, line_pat))
			ofs << matches[1] << to_iso(matches[2]) << matches[3];
		else
			ofs << line;
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
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