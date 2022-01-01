#include "String.h"

int main()
{
	String s{ "abcdefghij" };
	cout << s << '\n';
	s += 'k';
	s += 'l';
	s += 'm';
	s += 'n';
	cout << s << '\n';
	String s2 = "Hell";
	s2 += " and high water";
	cout << s2 << '\n';

	String s3 = "qwerty";
	s3 = s3;
	String s4 = "the quick brown fox jumped over the lazy dog";
	s4 = s4;
	cout << s3 << " " << s4 << "\n";
	cout << s + ". " + s3 + String(". ") + "Horsefeathers\n";

	String buf;
	while (cin >> buf && buf != "quit")
		cout << buf << " " << buf.size() << " " << buf.capacity() << '\n';
}