#include <iostream>
#include <string>
#include <locale>
#include <sstream>
using namespace std;

class Roman_int {
public:
	int I = 0;
	int V = 0;
	int X = 0;
	int L = 0;
	int C = 0;
	int D = 0;
	int M = 0;
	int as_int() const;
};

int Roman_int::as_int() const
{
	return 1 * I + 5 * V + 10 * X + 50 * L + 100 * C + 500 * D + 1000 * M;
}

class Roman_int_io : public locale::facet {
public:
	Roman_int_io(int i = 0) : locale::facet{ i } { }
	~Roman_int_io() { }
	virtual string to_alpha(Roman_int x) const = 0;
	virtual bool from_alpha(const string& s, Roman_int& x) const = 0;
	static locale::id id;
};
locale::id Roman_int_io::id;

ostream& operator<<(ostream& os, Roman_int x)
{
	locale loc{ os.getloc() };
	if (has_facet<Roman_int_io>(loc))
		return os << use_facet<Roman_int_io>(loc).to_alpha(x);
	return os << x.as_int();
}

istream& operator>>(istream& is, Roman_int& x)
{
	const locale& loc{ is.getloc() };
	if (has_facet<Roman_int_io>(loc)) {
		const Roman_int_io& f{ use_facet<Roman_int_io>(loc) };
		string buf;
		if (!(is >> buf && f.from_alpha(buf, x)))
			is.setstate(ios_base::failbit);
		return is;
	}
	is.setstate(ios::failbit);
	return is;
}

class US_Roman_int_io : public Roman_int_io {
public:
	string to_alpha(Roman_int) const;
	bool from_alpha(const string&, Roman_int&) const;
};

string US_Roman_int_io::to_alpha(Roman_int x) const
{
	int temp = x.as_int();
	ostringstream oss;
	while (temp != 0) {
		if (temp >= 1000) {
			oss << 'M';
			temp -= 1000;
		}
		else if (temp >= 900) {
			oss << "CM";
			temp -= 900;
		}
		else if (temp >= 500) {
			oss << 'D';
			temp -= 500;
		}
		else if (temp >= 400) {
			oss << "CD";
			temp -= 400;
		}
		else if (temp >= 100) {
			oss << 'C';
			temp -= 100;
		}
		else if (temp >= 90) {
			oss << "XC";
			temp -= 90;
		}
		else if (temp >= 50) {
			oss << 'L';
			temp -= 50;
		}
		else if (temp >= 40) {
			oss << "XL";
			temp -= 40;
		}
		else if (temp >= 10) {
			oss << 'X';
			temp -= 10;
		}
		else if (temp >= 9) {
			oss << "IX";
			temp -= 9;
		}
		else if (temp >= 5) {
			oss << 'V';
			temp -= 5;
		}
		else if (temp >= 4) {
			oss << "IV";
			temp -= 4;
		}
		else if (temp >= 1) {
			oss << 'I';
			temp -= 1;
		}
	}
	return oss.str();
}

bool US_Roman_int_io::from_alpha(const string& s, Roman_int& x) const
{
	for (int i = 0; i < s.size(); ++i) {
		switch (s[i]) {
		case 'M':
			++x.M;
			break;
		case 'D':
			++x.D;
			break;
		case 'C':
			if (i != s.size() && (s[i + 1] == 'M' || s[i + 1] == 'D'))
				--x.C;
			else
				++x.C;
			break;
		case 'L':
			++x.L;
			break;
		case 'X':
			if (i != s.size() && (s[i + 1] == 'C' || s[i + 1] == 'L'))
				--x.X;
			else
				++x.X;
			break;
		case 'V':
			++x.V;
			break;
		case 'I':
			if (i != s.size() && (s[i + 1] == 'X' || s[i + 1] == 'V'))
				--x.I;
			else
				++x.I;
			break;
		}
	}
	if (x.as_int() <= 0 || x.as_int() >= 4000)
		return false;
	return true;
}

int main()
{
	Roman_int x;
	locale loc(locale(), new US_Roman_int_io{});
	cout.imbue(loc);
	cin.imbue(loc);
	cin >> x;
	cout << x << endl;
}