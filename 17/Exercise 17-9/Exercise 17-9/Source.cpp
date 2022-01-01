#include "Calculator.h"

class Expr {
	char* expression;
public: 
	Expr(char* cs)
		:expression{ cs } { }

	int eval();
	void print();
};

int Expr::eval()
{
	using namespace Lexer;
	using Parser::expr;
	using Error::error;

	istringstream iss{ expression };
	ts.set_input(iss);
	return static_cast<int>(expr(true));
}

void Expr::print()
{
	cout << expression;
}

int main()
{
	Expr x("123 / 4 + 123 * 4 - 3"); 
	cout << "x = " << x.eval() << "\n"; 
	x.print();
}