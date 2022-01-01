#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

void rev(char s[])
{
	reverse(&s[0], &s[strlen(s)]);
}

int main()
{
	char s[] = "Hello World!";
	rev(s);
	cout << s;
}