#include <iostream>
#include <string>
#include <sstream>
#include <locale>
using namespace std;

struct Postal_code {
	string rep;
};

class Postal_code_io : public locale::facet {
public:
	Postal_code_io(int i = 0) : locale::facet{ i } { }
	~Postal_code_io() { }
	virtual string write(Postal_code) const = 0;
	virtual bool read(const string&, Postal_code&) const = 0;
	static locale::id id;
};
locale::id Postal_code_io::id;

ostream& operator<<(ostream& os, Postal_code x)
{
	locale loc{ os.getloc() };
	if (has_facet<Postal_code_io>(loc))
		return os << use_facet<Postal_code_io>(loc).write(x);
	return os << x.rep;
}

istream& operator>>(istream& is, Postal_code& x)
{
	const locale& loc{ is.getloc() };
	if (has_facet<Postal_code_io>(loc)) {
		const Postal_code_io& f{ use_facet<Postal_code_io>(loc) };
		string buf;
		if (!(getline(is, buf) && f.read(buf, x)))
			is.setstate(ios_base::failbit);
		return is;
	}
	is >> x.rep;
	return is;
}

class US_Postal_code_io : public Postal_code_io {
public:
	string write(Postal_code) const;
	bool read(const string&, Postal_code&) const;
};

string US_Postal_code_io::write(Postal_code x) const
{
	ostringstream oss;
	for (int i = 0; i < x.rep.size(); i++) {
		oss << x.rep[i];
		if (i == 1)
			oss << ' ';
	}
	return oss.str();
}

bool US_Postal_code_io::read(const string& s, Postal_code& x) const
{
	if (s.size() != 8)
		return false;

	ostringstream oss;
	for (int i = 0; i < s.size(); i++) {
		if (i > 2 && !isdigit(s[i]))
			return false;
		if (i != 2)
			oss << s[i];
	}
	x.rep = oss.str();
	return true;
}

class GB_Postal_code_io : public Postal_code_io {
public:
	string write(Postal_code) const;
	bool read(const string&, Postal_code&) const;
};

string GB_Postal_code_io::write(Postal_code x) const
{
	return x.rep;
}

bool GB_Postal_code_io::read(const string& s, Postal_code& x) const
{
	if (s.size() != 6)
		return false;

	x.rep = s;
	return true;
}

int main()
{
	Postal_code x;
	locale loc(locale(), new US_Postal_code_io{});
	cout.imbue(loc);
	cin.imbue(loc);
	cin >> x;
	cout << x << endl;
	locale loc2(locale(), new GB_Postal_code_io{});
	cout.imbue(loc2);
	cin.imbue(loc2);
	cin >> x;
	cout << x << endl;
}