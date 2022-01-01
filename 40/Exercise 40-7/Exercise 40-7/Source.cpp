#include <iostream>
#include <string>
#include <sstream>
#include <locale>
using namespace std;

struct Telephone {
	string rep;
};

class Telephone_io : public locale::facet {
public:
	Telephone_io(int i = 0) : locale::facet{ i } { }
	~Telephone_io() { }
	virtual string write(Telephone) const = 0;
	virtual bool read(const string&, Telephone&) const = 0;
	static locale::id id;
};
locale::id Telephone_io::id;

ostream& operator<<(ostream& os, Telephone x)
{
	locale loc{ os.getloc() };
	if (has_facet<Telephone_io>(loc))
		return os << use_facet<Telephone_io>(loc).write(x);
	return os << x.rep;
}

istream& operator>>(istream& is, Telephone& x)
{
	const locale& loc{ is.getloc() };
	if (has_facet<Telephone_io>(loc)) {
		const Telephone_io& f{ use_facet<Telephone_io>(loc) };
		string buf;
		if (!(getline(is, buf) && f.read(buf, x)))
			is.setstate(ios_base::failbit);
		return is;
	}
	is >> x.rep;
	return is;
}

class US_Telephone_io : public Telephone_io {
public:
	string write(Telephone) const;
	bool read(const string&, Telephone&) const;
};

string US_Telephone_io::write(Telephone x) const
{
	ostringstream oss;
	oss << '(';
	for (int i = 0; i < x.rep.size(); i++) {
		oss << x.rep[i];
		if (i == 2)
			oss << ") ";
		else if (i == 5)
			oss << '-';
	}
	return oss.str();
}

bool US_Telephone_io::read(const string& s, Telephone& x) const
{
	if (s.size() != 14)
		return false;

	ostringstream oss;
	for (int i = 0; i < s.size(); i++) {
		switch (i) {
		case 0: case 4: case 5: case 9:
			break;
		default:
			if (!isdigit(s[i]))
				return false;
			oss << s[i];
			break;
		}
	}
	x.rep = oss.str();
	return true;
}

class GB_Telephone_io : public Telephone_io {
public:
	string write(Telephone) const;
	bool read(const string&, Telephone&) const;
};

string GB_Telephone_io::write(Telephone x) const
{
	ostringstream oss;
	for (int i = 0; i < x.rep.size(); i++) {
		oss << x.rep[i];
		if (i == 3)
			oss << ' ';
	}
	return oss.str();
}

bool GB_Telephone_io::read(const string& s, Telephone& x) const
{
	if (s.size() != 11)
		return false;

	ostringstream oss;
	for (int i = 0; i < s.size(); i++) {
		if (i == 4) {}
		else if (!isdigit(s[i]))
			return false;
		else
			oss << s[i];
	}
	x.rep = oss.str();
	return true;
}

int main()
{
	Telephone x;
	locale loc(locale(), new US_Telephone_io{});
	cout.imbue(loc);
	cin.imbue(loc);
	cin >> x;
	cout << x << endl;
	locale loc2(locale(), new GB_Telephone_io{});
	cout.imbue(loc2);
	cin.imbue(loc2);
	cin >> x;
	cout << x << endl;
}