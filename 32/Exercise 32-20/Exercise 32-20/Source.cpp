#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

template <typename T>
bool is_palindrome(T first, T last)
{
	while (first < last) {
		if (*first != *last) 
			return false;
		++first;
		--last;
	}
	return true;
}

int main()
{
	for (string s; cin >> s; ) {
		auto x = s.c_str();
		cout << is_palindrome(&x[0], &x[strlen(x) - 1]) << '\n';
	}
}