#include <iostream>
#include <algorithm>
using namespace std;

void invert(int *ai, int size_d1, int size_d2)
{
	reverse(ai, ai + size_d1 * size_d2);
}

int main()
{
	int ai[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	invert(&ai[0][0], 3, 3);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << ai[i][j] << '\t';
		cout << '\n';
	}
}