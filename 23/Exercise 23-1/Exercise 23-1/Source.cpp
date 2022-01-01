#include <iostream>
using namespace std;

template <typename T, typename U>
T ptr_cast(U* p) {
	T t = dynamic_cast<T>(p);
	return t ? t : throw bad_cast();
}

class Ival_slider { virtual void v1() {} };
class BBslider{ virtual void v2() {} };

class BB_ival_slider : public Ival_slider, protected BBslider {
	// ...
};

void f(BB_ival_slider* p)
{
	Ival_slider* pi1 = p;
	Ival_slider* pi2 = ptr_cast<Ival_slider*>(p);
	cout << pi2 << '\n';

	// BBslider* pbb1 = p;
	BBslider* pbb2 = ptr_cast<BBslider*>(p);
	cout << pbb2 << '\n';
}

int main()
try {
	BB_ival_slider* p = new BB_ival_slider();
	f(p);
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