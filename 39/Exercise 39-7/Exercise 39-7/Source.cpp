#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
	string line;
	getline(cin, line);
	for (auto p = line.begin(); p != line.end(); p++) {
		switch (*p) {
		case 'z':
			*p = 'a';
			break;
		case 'Z':
			*p = 'A';
			break;
		case '9':
			*p = '0';
			break;
		default:
			if (isspace(*p))
				*p = 0;
			++*p;
		}
	}
	cout << line;
}