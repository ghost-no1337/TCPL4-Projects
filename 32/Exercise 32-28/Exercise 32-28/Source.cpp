#include <iostream>
#include <string>
#include "List.h"
using namespace std;

template <typename T>
void print_all(List<T>& lst)
{
	for (auto p = lst.begin(); p != lst.end(); p = p->succ)
		cout << p->value << '\n';
}

int main()
try {
	List<string> lst;
	cout << sizeof(lst) << ' ' << sizeof(Link<string>) << '\n';
	for (string s; cin >> s; )
		lst.insert(s);
	print_all(lst);
	cout << sizeof(lst);
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