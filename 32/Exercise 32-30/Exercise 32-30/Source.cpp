#include <iostream>
#include <stack>
using namespace std;

template <typename T>
void print(stack<T> s)
{
	cout << "{ ";
	while (s.size() > 0) {
		cout << s.top() << ' ';
		s.pop();
	}
	cout << '}';
}

int main()
{
	stack<int> si{ deque<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 } };
	print(si);
}