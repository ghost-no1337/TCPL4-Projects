#include <iostream>
#include <vector>
using namespace std;

class Vector {
    vector<float> v;
	unsigned int size;
public:
    Vector(vector<float> lf, unsigned int s);

    float operator[](unsigned int i);

    Vector& operator+=(float f);
    Vector& operator-=(float f);
    Vector& operator*=(float f);
    Vector& operator/=(float f);

	friend ostream& operator<<(ostream& os, Vector& v);
};

Vector::Vector(vector<float> lf, unsigned int s)
	:v{ lf }, size{ s }
{
	if (lf.size() != s)
		throw runtime_error("bad size");
}

float Vector::operator[](unsigned int i)
{
	return (0 <= i && i < size) ? v[i] : throw runtime_error("bad index");
}

Vector& Vector::operator+=(float f)
{
	for (float& vf : v)
		vf += f;
	return *this;
}

Vector& Vector::operator-=(float f)
{
	for (float& vf : v)
		vf -= f;
	return *this;
}

Vector& Vector::operator*=(float f)
{
	for (float& vf : v)
		vf *= f;
	return *this;
}

Vector& Vector::operator/=(float f)
{
	for (float& vf : v)
		vf /= f;
	return *this;
}

Vector operator+(Vector v, float f)
{
	return v += f;
}

Vector operator+(float f, Vector v)
{
	return v += f;
}

Vector operator-(Vector v, float f)
{
	return v -= f;
}

Vector operator-(float f, Vector v)
{
	return v -= f;
}

Vector operator*(Vector v, float f)
{
	return v *= f;
}

Vector operator*(float f, Vector v)
{
	return v *= f;
}

Vector operator/(Vector v, float f)
{
	return v /= f;
}

Vector operator/(float f, Vector v)
{
	return v /= f;
}

ostream& operator<<(ostream& os, Vector& v)
{
	for (int i = 0; i < v.size; i++)
		os << v[i];
	return os;
}

int main()
{
	vector<float> vf;
	float f = 0;
	while (cin >> f)
		vf.push_back(f);

	Vector v{ vf, vf.size() };
	cout << v;
	cin >> f;
	cout << v + f << '\n'
		<< v - f << '\n'
		<< v * f << '\n'
		<< v / f << '\n';
}