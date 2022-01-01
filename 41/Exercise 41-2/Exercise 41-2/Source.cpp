#include <iostream>
#include <valarray>
using namespace std;

template <typename T, typename Fct>
void apply(valarray<T>& orig, Fct f)
{
	for (T& t : orig)
		f(t);
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
	valarray<int> vai{ 1, 2, 3, 4, 5 };
	apply(vai, Plus<int>{ 2 });
	for (int i : vai)
		cout << i << '\n';
}