#pragma once
#include <iostream>
#include <string>
using namespace std;

template<int M, int K, int S>
struct Unit {
	enum { m = M, kg = K, s = S };
};

using M = Unit<1, 0, 0>;
using Kg = Unit<0, 1, 0>;
using S = Unit<0, 0, 1>;
using MpS = Unit<1, 0, -1>;
using MpS2 = Unit<1, 0, -2>;

template<typename U1, typename U2>
struct Uplus {
	using type = Unit<U1::m + U2::m, U1::kg + U2::kg, U1::s + U2::s>;
};

template<typename U1, typename U2>
using Unit_plus = typename Uplus<U1, U2>::type;

template<typename U1, typename U2>
struct Uminus {
	using type = Unit<U1::m - U2::m, U1::kg - U2::kg, U1::s - U2::s>;
};

template<typename U1, typename U2>
using Unit_minus = typename Uminus<U1, U2>::type;

template<typename U>
struct Quantity {
	long double val;
	explicit Quantity(long double d) : val{ d } {}
};

template<typename U>
Quantity<U> operator+(Quantity<U> x, Quantity<U> y)
{
	return Quantity<U>{ x.val + y.val };
}

template<typename U>
Quantity<U> operator-(Quantity<U> x, Quantity<U> y)
{
	return Quantity<U>{ x.val - y.val };
}

template<typename U1, typename U2>
Quantity<Unit_plus<U1, U2>> operator *(Quantity<U1> x, Quantity<U2> y)
{
	return Quantity<Unit_plus<U1, U2>>{ x.val * y.val };
}

template<typename U1, typename U2>
Quantity<Unit_minus<U1, U2>> operator/(Quantity<U1> x, Quantity<U2> y)
{
	return Quantity<Unit_minus<U1, U2>>{ x.val / y.val };
}

template<typename U>
Quantity<U> operator *(Quantity<U> x, long double y)
{
	return Quantity<U>{ x.val * y };
}

template<typename U>
Quantity<U> operator *(long double x, Quantity<U> y)
{
	return Quantity<U>{ x * y.val };
}

const Quantity<M> operator"" _m(long double d) { return Quantity<M>{d}; }
const Quantity<Kg> operator"" _kg(long double d) { return Quantity<Kg>{d}; }
const Quantity<S> operator"" _s(long double d) { return Quantity<S>{d}; }

template<typename U>
Quantity<Unit_plus<U, U>> square(Quantity<U> x)
{
	return Quantity<Unit_plus<U, U>>(x.val * x.val);
}

template<typename U>
bool operator==(Quantity<U> x, Quantity<U> y)
{
	return x.val == y.val;
}

template<typename U>
bool operator!=(Quantity<U> x, Quantity<U> y)
{
	return x.val != y.val;
}

string suffix(int u, const char* x)
{
	string suf;
	if (u) {
		suf += x;
		if (1 < u) suf += '0' + u;

		if (u < 0) {
			suf += '-';
			suf += '0' - u;
		}
	}
	return suf;
}

template<typename U>
ostream& operator<<(ostream& os, Quantity<U> v)
{
	return os << v.val << suffix(U::m, "m") << suffix(U::kg, "kg") << suffix(U::s, "s");
}