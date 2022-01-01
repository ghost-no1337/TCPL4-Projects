#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cctype>
using namespace std;

namespace Parser {
	double expr(bool);
}

namespace Lexer {
	enum class Kind : char {
		name, number, end,
		plus = '+', minus = '-', mul = '*', div = '/', print = ';', assign = '=', lp = '(', rp = ')'
	};

	struct Token {
		Kind kind;
		string string_value;
		double number_value;
	};

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

	extern Token_stream ts;
}

namespace Table {
	extern map<string, double> table;
}

namespace Error {
	extern int no_of_errors;
	double error(const string& s);
}

namespace Driver {
	void calculate();
}