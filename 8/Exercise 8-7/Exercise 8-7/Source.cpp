#include <iostream>
#include <string>
using namespace std;

void swap(int* i1, int* i2)
{
	int temp = *i1;
	*i1 = *i2;
	*i2 = temp;
}

void swap(int& i1, int& i2)
{
	int temp = i1;
	i1 = i2;
	i2 = temp;
}

int main()
{
	int i1 = 1;
	int i2 = 2;

	int *pi1 = &i1;
	int *pi2 = &i2;

	int &ri1 = i1;
	int &ri2 = i2;

	swap(pi1, pi2);
	cout << "Method 1 result: " << i1 << ", " << i2 << '\n';

	swap(ri1, ri2);
	cout << "Method 2 result: " << i1 << ", " << i2 << '\n';
}