#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <list>
using namespace std;

template <typename Iter, typename Oper>
void out(Iter first, Iter last, Oper op)
{
	while (first != last) {
		op(*first);
		++first;
	}
}

int main()
{
	char* acs[] = { "Hello ", "World " };
	out(&acs[0], &acs[2], printf);
	list<string> ls{ "Hello ", "World " };
	out(ls.begin(), ls.end(), 
		[](const string& s) {cout << s; });
}