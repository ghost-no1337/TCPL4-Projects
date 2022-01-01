#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cctype>
using namespace std;

enum class Kind : char {
	name, number, end,
	plus_t = '+', minus_t = '-', mul = '*', div = '/', print = ';', assign = '=', lp = '(', rp = ')'
};

map<string, double> table;

struct Token {
	Kind kind;
	string string_value;
	double number_value;
};

// Error Handling

int no_of_errors;

double error(const string& s)
{
	no_of_errors++;
	cerr << "error: " << s << '\n';
	return 1;
}

// Input

class Token_stream {
public:
	Token_stream(istream& s) : ip{ &s }, owns{ false } { }
	Token_stream(istream* p) : ip{ p }, owns{ true } { }

	~Token_stream() { close(); }

	Token get();
	const Token& current() { return ct; }

	void set_input(istream& s) { close(); ip = &s; owns = false; }
	void set_input(istream* p) { close(); ip = p; owns = true; }
private:
	void close() { if (owns) delete ip; }

	istream* ip;
	bool owns;
	Token ct{ Kind::end };
};

Token Token_stream::get()
{
	char ch;
	do {
		if (!ip->get(ch))
			return ct = { Kind::end };
	} while (ch != '\n' && isspace(ch));

	switch (ch) {
	case ';':
	case '\n':
		return ct = { Kind::print };
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
	case '=':
		return ct = { static_cast<Kind>(ch) };
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
	case '.':
		ip->putback(ch);
		*ip >> ct.number_value;
		ct.kind = Kind::number;
		return ct;
	default:
		if (isalpha(ch)) {
			ct.string_value = ch;
			while (ip->get(ch) && isalnum(ch))
				ct.string_value += ch;
			ip->putback(ch);
			ct.kind = Kind::name;
			return ct;
		}
		error("bad token");
		return ct = { Kind::print };
	}
}

Token_stream ts{ cin };

// The Parser

double plus_f(double d1, double d2)
{
	long double ld1 = d1;
	long double ld2 = d2;
	if (ld1 + ld2 == d1 + d2)
		return d1 + d2;
	error("overflow detected");
}

double minus_f(double d1, double d2)
{
	long double ld1 = d1;
	long double ld2 = d2;
	if (ld1 - ld2 == d1 - d2)
		return d1 - d2;
	error("overflow detected");
}

double multiply(double d1, double d2)
{
	long double ld1 = d1;
	long double ld2 = d2;
	if (ld1 * ld2 == d1 * d2)
		return d1 * d2;
	error("overflow detected");
}

double divide(double d1, double d2)
{
	long double ld1 = d1;
	long double ld2 = d2;
	if (ld1 / ld2 == d1 / d2)
		return d1 / d2;
	error("overflow detected");
}

double expr(bool);

double prim(bool get)
{
	if (get) ts.get(); // read next token

	switch (ts.current().kind) {
	case Kind::number:
	{
		double v = ts.current().number_value;
		ts.get();
		return v;
	}
	case Kind::name:
	{
		double& v = table[ts.current().string_value];
		if (ts.get().kind == Kind::assign) v = expr(true);
		return v;
	}
	case Kind::minus_t:
		return -prim(true);
	case Kind::lp:
	{
		auto e = expr(true);
		if (ts.current().kind != Kind::rp)
			return error("')' expected");
		ts.get();
		return e;
	}
	default:
		return error("primary expected");
	}
}

double term(bool get)
{
	double left = prim(get);

	while (true) {
		switch (ts.current().kind) {
		case Kind::mul:
			left = multiply(left, prim(true));
			break;
		case Kind::div:
			if (auto d = prim(true)) {
				left = divide(left, d);
				break;
			}
			return error("divide by 0");
		default:
			return left;
		}
	}
}

double expr(bool get)
{
	double left = term(get);

	while (true) {
		switch (ts.current().kind) {
		case Kind::plus_t:
			left = plus_f(left, term(true));
			break;
		case Kind::minus_t:
			left = minus_f(left, term(true));
			break;
		default:
			return left;
		}
	}
}

// The Driver

void calculate()
{
	while (true) {
		cout << "> ";
		ts.get();
		if (ts.current().kind == Kind::end)
			break;
		if (ts.current().kind == Kind::print)
			continue;
		cout << "= " << expr(false) << '\n';
	}
}

int main(int argc, char* argv[])
{
	switch (argc) {
	case 1:
		break;
	case 2:
		ts.set_input(new istringstream{ argv[1] });
		break;
	default:
		error("too many arguments");
		return 1;
	}

	table["pi"] = 3.1415926535897932385;
	table["e"] = 2.7182818284590452354;

	calculate();

	return no_of_errors;
}