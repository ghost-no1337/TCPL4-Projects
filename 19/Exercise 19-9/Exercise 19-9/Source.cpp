#include <iostream>
#include <vector>
using namespace std;

class Vec4 {
	vector<float> v;
public:
	Vec4(vector<float> lf);

	float operator[](unsigned int i);

	Vec4& operator+=(float f);
	Vec4& operator-=(float f);
	Vec4& operator*=(float f);
	Vec4& operator/=(float f);
};

Vec4::Vec4(vector<float> lf)
	:v{ lf }
{
	if (lf.size() != 4)
		throw runtime_error("bad size");
}

float Vec4::operator[](unsigned int i)
{
	return (0 <= i && i < 4) ? v[i] : throw runtime_error("bad index");
}

Vec4& Vec4::operator+=(float f)
{
	for (float& vf : v)
		vf += f;
	return *this;
}

Vec4& Vec4::operator-=(float f)
{
	for (float& vf : v)
		vf -= f;
	return *this;
}

Vec4& Vec4::operator*=(float f)
{
	for (float& vf : v)
		vf *= f;
	return *this;
}

Vec4& Vec4::operator/=(float f)
{
	for (float& vf : v)
		vf /= f;
	return *this;
}

Vec4 operator+(Vec4 v, float f)
{
	return v += f;
}

Vec4 operator+(float f, Vec4 v)
{
	return v += f;
}

Vec4 operator-(Vec4 v, float f)
{
	return v -= f;
}

Vec4 operator-(float f, Vec4 v)
{
	return v -= f;
}

Vec4 operator*(Vec4 v, float f)
{
	return v *= f;
}

Vec4 operator*(float f, Vec4 v)
{
	return v *= f;
}

Vec4 operator/(Vec4 v, float f)
{
	return v /= f;
}

Vec4 operator/(float f, Vec4 v)
{
	return v /= f;
}

ostream& operator<<(ostream& os, Vec4& v)
{
	for (int i = 0; i < 4; i++)
		os << v[i] << ' ';
	return os;
}

int main()
{
	vector<float> vf;
	float f = 0;
	for (int i = 0; i < 4; i++) {
		cin >> f;
		vf.push_back(f);
	}

	Vec4 v{ vf };
	cout << v;
	cin >> f;
	cout << v + f << '\n'
		<< v - f << '\n'
		<< v * f << '\n'
		<< v / f << '\n';
}