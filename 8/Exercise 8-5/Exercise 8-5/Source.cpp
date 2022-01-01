#include <iostream>
using namespace std;

template <typename T>
int number_of_elem(T* first, T* end)
{
	if (!first || !end)
		return 0;
	int count = 0;
	for (T* p = first; p != end; p++) {
		if (p)
			++count;
		else
			return 0;
	}
	return count;
}

int main()
{
	int ai[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	cout << number_of_elem(&ai[0], &ai[10]);
}