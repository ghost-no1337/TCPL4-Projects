#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

template <typename Iter1, typename Iter2>
pair<Iter1, Iter2> match(Iter1 first1, Iter1 last1, Iter2 first2)
{
	while ((first1 != last1) && (*first1 != *first2)) {
		++first1; 
		++first2;
	}
	return make_pair(first1, first2);
}

template <typename Iter1, typename Iter2, typename Fct>
pair<Iter1, Iter2> match(Iter1 first1, Iter1 last1, Iter2 first2, Fct f)
{
	while ((first1 != last1) && !f(*first1, *first2)) {
		++first1;
		++first2;
	}
	return make_pair(first1, first2);
}

int main()
{
	vector<int> vi1{ 1, 2, 3, 4, 5 };
	vector<int> vi2{ 5, 4, 3, 2, 1 };
	auto p = match(vi1.begin(), vi1.end(), vi2.begin());
	cout << *(p.first) << ' ' << *(p.second) << '\n';
}