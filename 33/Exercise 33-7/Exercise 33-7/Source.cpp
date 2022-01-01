#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <vector>
using namespace std;

int main()
{
	ostream_iterator<double> os_iter{ cout, "\n" };
	vector<double> v(100);
	iota(v.begin(), v.end(), 1);
	transform(v.begin(), v.end(), os_iter, [](double d) { return d * d; });
	transform(v.begin(), v.end(), os_iter, [](double d) { return sqrt(d); });
}