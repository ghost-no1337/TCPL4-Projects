#include <iostream>

namespace std {
	class Ostream {
	public:
		Ostream(ostream& ost);
		~Ostream();

		friend Ostream& operator<<(Ostream& os, const char* ch);
	private:
		std::ostream* os;
	};

	Ostream::Ostream(ostream& ost)
		:os{ &ost }
	{
		*os << "Initialize\n";
	}

	Ostream::~Ostream()
	{
		*os << "Clean up\n";
	}

	Ostream& operator<<(Ostream& ost, const char* ch)
	{
		*(ost.os) << ch;
		return ost;
	}

	Ostream Cout{ cout };
}

#define cout Cout

int main()
{
	std::cout << "Hello, world!\n";
}