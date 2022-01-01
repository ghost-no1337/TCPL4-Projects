#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename Cont>
Cont merge(Cont c1, Cont c2)
{
	Cont c(c1.size() + c2.size());
	auto p = copy(c1.begin(), c1.end(), c.begin());
	copy(c2.begin(), c2.end(), p);
	return c;
}

int main()
{
	vector<int> v1{ 1, 2, 3, 4, 5 };
	vector<int> v2{ 6, 7, 8, 9, 0 };

	vector<int> x = merge(v1, v2);
	for (int i : x)
		cout << i << ' ';
}