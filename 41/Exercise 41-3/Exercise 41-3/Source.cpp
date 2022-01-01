#include <iostream>
#include <valarray>
using namespace std;

template<typename T>
class Slice_iter {
	valarray<T>* v;
	bool owned;
	slice s;
	size_t curr;

	T& ref(size_t i) const { return (*v)[s.start() + i * s.stride()]; }
public:
	Slice_iter(valarray<T>* vv, slice ss, size_t pos = 0)
		:v{ vv }, owned{ true }, s { ss	}, curr{ pos } { }
	Slice_iter(valarray<T>& vv, slice ss, size_t pos = 0)
		:v{ &vv }, owned{ false }, s{ ss }, curr{ pos } { }
	~Slice_iter() { if (owned) delete v; }

	Slice_iter end() const { return Slice_iter{ *v, s, s.size() }; }

	Slice_iter& operator++() { ++curr; return *this; }
	Slice_iter operator++(int) { Slice_iter t = *this; ++curr; return t; }

	T& operator[](size_t i) { return ref(i); }
	T& operator()(size_t i) { return ref(i); }
	T& operator*() { return ref(curr); }

	bool operator==(const Slice_iter& q) const
	{
		return curr == q.curr && s.stride() == q.s.stride() && s.start() == q.s.start();
	}

	bool operator!=(const Slice_iter& q) const
	{
		return !(*this == q);
	}

	bool operator<(const Slice_iter& q) const
	{
		return curr < q.curr && s.stride() == q.s.stride() && s.start() == q.s.start();
	};
};

int main()
{
	valarray<int> v{
		00, 01, 02, 03,
		10, 11, 12, 13,
		20, 21, 22, 23
	};

	for (Slice_iter<int> p{ v, slice{ 0, 4, 1 } }; p != p.end(); p++)
		cout << *p << ' ';
	cout << '\n';
	for (Slice_iter<int> p{ v, slice{ 1, 3, 4 } }; p != p.end(); p++)
		cout << *p << ' ';
}