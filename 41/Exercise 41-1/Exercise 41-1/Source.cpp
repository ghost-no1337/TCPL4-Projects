#include <iostream>
#include <valarray>
using namespace std;

template <typename T, typename Fct>
valarray<T> apply(valarray<T> orig, Fct f)
{
	for (T& t : orig)
		f(t);
	return orig;
}

template <typename T>
class Plus {
public:
	Plus(T t) :pls{ t } { }
	void operator()(T& t) { t += pls; }
private:
	T pls;
};

int main()
{
	valarray<int> vai { 1, 2, 3, 4, 5 };
	valarray<int> vai2 = apply(vai, Plus<int>{ 2 });
	for (int i : vai2)
		cout << i << '\n';
}