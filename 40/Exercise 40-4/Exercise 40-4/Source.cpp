#include <iostream>
#include <string>
#include <locale>
using namespace std;

struct Bool {
	bool b;
	operator bool() { return b; }
};

class Bool_io : public locale::facet {
public:
	Bool_io(int i = 0) : locale::facet{ i } { }
	~Bool_io() { }
	virtual const string& to_alpha(Bool x) const = 0;
	virtual bool from_alpha(const string& s, Bool& x) const = 0;
	static locale::id id;
};
locale::id Bool_io::id;

ostream& operator<<(ostream& os, Bool x)
{
	locale loc{ os.getloc() };
	if (has_facet<Bool_io>(loc))
		return os << use_facet<Bool_io>(loc).to_alpha(x);
	return os << static_cast<int>(x);
}

istream& operator>>(istream& is, Bool& x)
{
	const locale& loc{ is.getloc() };
	if (has_facet<Bool_io>(loc)) {
		const Bool_io& f{ use_facet<Bool_io>(loc) };
		string buf;
		if (!(is >> buf && f.from_alpha(buf, x)))
			is.setstate(ios_base::failbit);
		return is;
	}
	is >> x.b;
	return is;
}

class US_bool_io : public Bool_io {
	static const string alphas[];
public:
	const string& to_alpha(Bool) const;
	bool from_alpha(const string&, Bool&) const;
};

const string US_bool_io::alphas[] = {
	"false", "true"
};

const string& US_bool_io::to_alpha(Bool x) const
{
	return alphas[static_cast<int>(x)];
}

bool US_bool_io::from_alpha(const string& s, Bool& x) const
{
	const string* p = find(begin(alphas), end(alphas), s);
	if (p == end(alphas))
		return false;
	x.b = p - begin(alphas);
	return true;
}

int main()
{
	Bool x;
	cin >> x;
	cout << x << endl;
	locale loc(locale(), new US_bool_io{});
	cout.imbue(loc);
	cin.imbue(loc);
	cin >> x;
	cout << x << endl;
}