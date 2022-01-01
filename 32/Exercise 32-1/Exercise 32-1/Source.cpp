#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

int main()
{
	vector<char> alphabetical(26);
	iota(alphabetical.begin(), alphabetical.end(), 'a');
	for (char ch : alphabetical)
		cout << ch << ' ';
	cout << '\n';
	sort(alphabetical.begin(), alphabetical.end(), greater<char>());
	for (char ch : alphabetical)
		cout << ch << ' ';
}