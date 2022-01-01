#include <iostream>
#include <vector>
using namespace std;

void copy_int(int i[], int size, vector<int>& vi)
{
	for (int* p = i; p - i < size; p++)
		if (*p != 0 && (*p) % 2 == 0)
			vi.push_back(*p);
}

int main()
{
	int i[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> vi;
	copy_int(i, 10, vi);
	for (int i : vi)
		cout << i << '\n';
}