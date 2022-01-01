#include <iostream>
#include <exception>
using namespace std;

template<typename T>
class Ptr {
	T* ptr;
	T* arr;
	int sz;

	void range_check(T* p);
public:
	Ptr(T* p, T* a, int s);
	Ptr(T* p);

	Ptr& operator++();
	Ptr operator++(int);

	Ptr& operator--();
	Ptr operator--(int);

	T& operator*();
	T* operator->();
};

template<typename T>
void Ptr<T>::range_check(T* p)
{
	if (p < arr || p >= arr + sz)
		throw runtime_error("ptr out of range");
}

template<typename T>
Ptr<T>::Ptr(T* p, T* a, int s)
	:ptr{ p }, arr{ a }, sz{ s }
{
	range_check(ptr);
}

template<typename T>
Ptr<T>::Ptr(T* p)
	:ptr{ p }, arr{ nullptr }, sz{ 0 } { }

template<typename T>
Ptr<T>& Ptr<T>::operator++()
{
	range_check(ptr + 1);
	++ptr;
	return *this;
}

template<typename T>
Ptr<T> Ptr<T>::operator++(int)
{
	range_check(ptr + 1);
	Ptr<T> old{ ptr, arr, sz };
	++ptr;
	return old;
}

template<typename T>
Ptr<T>& Ptr<T>::operator--()
{
	range_check(ptr - 1);
	--ptr;
	return *this;
}

template<typename T>
Ptr<T> Ptr<T>::operator--(int)
{
	range_check(ptr - 1);
	Ptr<T> old{ ptr, arr, sz };
	--ptr;
	return old;
}

template<typename T>
T& Ptr<T>::operator*()
{
	return *ptr;
}

template<typename T>
T* Ptr<T>::operator->()
{
	return ptr;
}

int main()
try {
	int ai[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Ptr<int> p{ &ai[0], &ai[0], 10 };
	cout << *p << '\n';
	for (int i = 0; i < 10; i++)
		cout << *++p << '\n';
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	char ch; cin >> ch;
	return 1;
}
catch (...) {
	cerr << "error: unknown error\n";
	char ch; cin >> ch;
	return -1;
}