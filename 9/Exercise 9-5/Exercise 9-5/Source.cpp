#include <iostream>
#include <string>
#include <map>
using namespace std;

enum class Season {
	spring, summer, autumn, winter
};

map<int, string> output;

ostream& operator<<(ostream& os, const Season& s)
{
	return os << output[static_cast<int>(s)];
}

Season& operator++(Season &s)
{
	s = (s == Season::winter) ? Season::spring : static_cast<Season>(static_cast<int>(s) + 1);
	return s;
}

Season& operator--(Season &s)
{
	s = (s == Season::spring) ? Season::winter : static_cast<Season>(static_cast<int>(s) - 1);
	return s;
}

int main()
{
	output[static_cast<int>(Season::spring)] = "spring";
	output[static_cast<int>(Season::summer)] = "summer";
	output[static_cast<int>(Season::autumn)] = "autumn";
	output[static_cast<int>(Season::winter)] = "winter";

	cout << Season::spring << '\n'
		<< Season::summer << '\n'
		<< Season::autumn << '\n'
		<< Season::winter << '\n';
}