#include <iostream>
#include <vector>
using namespace std;

void read_chars(vector<char>& vc)
{
	bool ignoring = false;
	bool print_all = false;
	for (char ch; cin.get(ch) && ch != '|'; ) {
		if (print_all) {
			if (ch == '"')
				print_all = false;
			goto other_chars;
		}
		switch (ch) {
		case '/':
			cin.get(ch);
			if (ch == '/') {
				while (cin.get(ch) && ch != '\n');
				break;
			}
			else if (ch == '*') {
				ignoring = true;
				break;
			}
			goto other_chars;
		case '*':
			cin.get(ch);
			if (ch == '/')
				if (ignoring) {
					ignoring = false;
					break;
				}
				else
					throw runtime_error("'/*', '*/' mismatch");
			goto other_chars;
		case '"':
			if (!ignoring)
				print_all = true;
		default:
		other_chars:
			if (!ignoring)
				vc.push_back(ch);
		}
	}
}

int main()
try {
	cout << "Please enter a piece of code: (Enter '|' to exit)\n";
	vector<char> chars;
	read_chars(chars);
	for (char ch : chars)
		cout << ch;
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