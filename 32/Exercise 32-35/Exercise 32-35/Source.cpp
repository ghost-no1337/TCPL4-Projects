#include <iostream>
using namespace std;

bool is_palindrome(const char* first, const char* last)
{
	while (first < last) {
		if (*first != *last)
			return false;
		++first;
		--last;
	}
	return true;
}

bool is_palindrome(char ch[], int sz)
{
	if (sz < 3)
		return is_palindrome(ch, ch + sz);

	for (int i = 3; i <= sz; i++)
		if (is_palindrome(ch, ch + i))
			return true;
	return false;
}

int main()
{
	char ch[] = "Hello World!";
	char ch2[] = "HellolleH";
	char ch3[] = "HeleH World!";
	cout << ch << '\n'
		<< ch2 << '\n'
		<< ch3 << '\n'
		<< is_palindrome(ch, 13) << '\n'
		<< is_palindrome(ch2, 10) << '\n'
		<< is_palindrome(ch3, 13) << '\n';
}