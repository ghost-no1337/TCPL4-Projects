#include "dc.h"

namespace Table {
	map<string, double> table;
}

void Driver::calculate()
{
	using namespace Lexer;

	while (true) {
		cout << "> ";
		ts.get();
		if (ts.current().kind == Kind::end)
			break;
		if (ts.current().kind == Kind::print)
			continue;
		cout << "= " << Parser::expr(false) << '\n';
	}
}

int main(int argc, char* argv[])
{
	using namespace Lexer;
	using Table::table;

	switch (argc) {
	case 1:
		break;
	case 2:
		ts.set_input(new istringstream{ argv[1] });
		break;
	default:
		Error::error("too many arguments");
		return 1;
	}

	table["pi"] = 3.1415926535897932385;
	table["e"] = 2.7182818284590452354;

	Driver::calculate();

	return Error::no_of_errors;
}