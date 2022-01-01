#include <iostream>
#include <cctype>
using namespace std;

int main()
{
	for (char ch = 0; ch < CHAR_MAX; ch++)
		if (islower(ch))
			cout << ch << '\t';
	cout << '\n';
	for (char ch = 0; ch < CHAR_MAX; ch++)
		if (isalpha(ch))
			cout << ch << '\t';
	cout << '\n';
	for (char ch = 0; ch < CHAR_MAX; ch++)
		if (islower(ch) || isdigit(ch))
			cout << ch << '\t';
	cout << '\n';
	for (char ch = 0; ch < CHAR_MAX; ch++)
		if (ispunct(ch))
			cout << ch << '\t';
	cout << '\n';
	for (char ch = 0; ch < CHAR_MAX; ch++)
		if (iscntrl(ch))
			cout << static_cast<int>(ch) << '\t';
	cout << '\n';
	for (char ch = 0; ch < CHAR_MAX; ch++)
		if (isspace(ch))
			cout << ch << '\t';
	cout << '\n';
	for (char ch = 0; ch < CHAR_MAX; ch++)
		if (isspace(ch))
			cout << static_cast<int>(ch) << '\t';
	cout << '\n';
	for (char ch = 0; ch < CHAR_MAX; ch++)
		if (isprint(ch))
			cout << static_cast<int>(ch) << '\t';
}