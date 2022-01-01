#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <functional>
using namespace std;

template<typename List>
void sort_list(List& lst)
{
	using T = lst.value_type;
	vector<T> v{ lst.begin(), lst.end() };
	sort(v.begin(), v.end());
	copy(v.begin(), v.end(), lst.begin());
}

template<typename List, typename Fct>
void sort_list(List& lst, Fct f)
{
	using T = lst.value_type;
	vector<T> v{ lst.begin(), lst.end() };
	sort(v.begin(), v.end(), f);
	copy(v.begin(), v.end(), lst.begin());
}

int main()
{
	list<int> lst{ 1, 3, 5, 2, 4 };
	sort_list(lst);
	for_each(lst.begin(), lst.end(), [](int i) { cout << i << ' '; });
	cout << '\n';

	sort_list(lst, greater<int>{});
	for_each(lst.begin(), lst.end(), [](int i) { cout << i << ' '; });
}