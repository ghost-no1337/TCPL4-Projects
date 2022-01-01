#include <iostream>
using namespace std;

class RINT {
	int v;
public:
	RINT(int i = 0)
		:v{ i } { }
	RINT& operator=(int i) { v = i; return *this; }

	friend RINT operator+(RINT R);
	friend RINT operator-(RINT R);

	friend RINT operator+(RINT R1, RINT R2);
	friend RINT operator-(RINT R1, RINT R2);
	friend RINT operator*(RINT R1, RINT R2);
	friend RINT operator/(RINT R1, RINT R2);
	friend RINT operator%(RINT R1, RINT R2);

	friend ostream& operator<<(ostream& os, RINT R);
};

RINT operator+(RINT R)
{
	return R;
}

RINT operator-(RINT R)
{
	return RINT{ -R.v };
}

RINT operator+(RINT R1, RINT R2)
{
	return RINT{ R1.v + R2.v };
}

RINT operator-(RINT R1, RINT R2)
{
	return RINT{ R1.v - R2.v };
}

RINT operator*(RINT R1, RINT R2)
{
	return RINT{ R1.v * R2.v };
}

RINT operator/(RINT R1, RINT R2)
{
	return RINT{ R1.v / R2.v };
}

RINT operator%(RINT R1, RINT R2)
{
	return RINT{ R1.v % R2.v };
}

ostream& operator<<(ostream& os, RINT R)
{
	return os << R.v;
}

int main()
{
	int i1 = 0, i2 = 0;
	cin >> i1 >> i2;
	RINT R1 = i1;
	RINT R2 = i2;
	RINT plus = R1 + R2;
	cout << plus;
}