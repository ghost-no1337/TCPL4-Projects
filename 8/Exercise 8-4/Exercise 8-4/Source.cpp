#include <iostream>
using namespace std;

int number_of_char(char* first, char* end)
{
	if (!first || !end)
		return 0;
	int count = 0;
	for (char* p = first; p != end; p++) {
		if (p)
			if (*p == 0)
				return count;
			else
				++count;
		else
			return 0;
	}
	return count;
}

int main()
{
	char string[] = "Hello, World!";
	cout << number_of_char(&string[0], &string[10]);
}