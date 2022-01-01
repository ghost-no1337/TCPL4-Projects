#include "List.h"
#include <iostream>

int main()
{
	List<int> lst { new int{ 1 }, new int{ 2 }, new int{ 3 }, new int{ 4 }, new int{ 5 } };
	for (auto p = lst.begin(); p != lst.end(); p++)
		if (**p == 3) {
			lst.erase(*p);
			break;
		}
	for (auto p = lst.begin(); p != lst.end(); p++)
		cout << **p << ' ';
}