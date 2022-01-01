#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <regex>
using namespace std;

typedef vector<char> Line;

class Text_iterator {
	list<Line>::iterator ln;
	Line::iterator pos;
public:
	Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		:ln{ ll }, pos{ pp } { }

	list<Line>::iterator line() const { return ln; }
	Line::iterator position() const { return pos; }

	char& operator*() { return *pos; }
	Text_iterator& operator++();
	Text_iterator& operator--();

	bool operator==(const Text_iterator& other) const
	{
		return ln == other.ln && pos == other.pos;
	}
	bool operator!=(const Text_iterator& other) const
	{
		return !(*this == other);
	}
};

Text_iterator& Text_iterator::operator++()
{
	++pos;
	if (pos == (*ln).end()) {
		++ln;
		pos = (*ln).begin();
	}
	return *this;
}

Text_iterator& Text_iterator::operator--()
{
	if (pos == (*ln).begin()) {
		--ln;
		pos = (*ln).end();
	}
	--pos;
	return *this;
}

template <typename T>
T to(const string& s) 
{
	istringstream iss{ s };
	T t;
	iss >> t;
	return iss ? t : throw runtime_error("cannot extract information from string");
}

template <>
Line to<Line>(const string& s)
{
	Line l;
	for (char ch : s)
		l.push_back(ch);
	return l;
}

class Document {
	list<Line> lines;
public:
	Document(istream& is);

	list<Line>& line() { return lines; }

	Text_iterator begin()
	{
		return Text_iterator{ lines.begin(), (*lines.begin()).begin() };
	}
	Text_iterator end()
	{
		auto last = lines.end();
		--last;
		return Text_iterator{ last, (*last).end() };
	}
};

Document::Document(istream& is)
{
	for (string s; getline(is, s); )
		lines.push_back(to<Line>(s));
}

void print(Document& d, ostream& os)
{
	for (auto p = d.begin(); p != --d.end(); ++p) 
		os << *p;
	os << *(--d.end());
}

void erase_line(Document& d, int n)
{
	if (n < 0 || d.line().size() - 1 <= n) return;
	auto p = d.line().begin();
	advance(p, n);
	d.line().erase(p);
}

void insert_line(Document& d, int n, Line line)
{
	if (n < 0 || d.line().size() - 1 <= n) return;
	auto p = d.line().begin();
	advance(p, n);
	d.line().insert(p, line);
}

template<typename Iter>
void advance(Iter& p, int n)
{
	while (0 < n) { ++p; --n; }
}

struct Operation {
	enum Oper { undo_t, insert_t, delete_t };
	Operation(Document& d)
		:doc{ d } { }
	void set_oper(Oper oper, int i, Line& l = Line{});
	void reset_oper();
	void do_oper();

	Document& doc;
	Oper operation{ undo_t };
	int lineno;
	Line line;
};

void Operation::set_oper(Oper oper, int i, Line& l)
{
	operation = oper;
	lineno = i;
	line = l;
}

void Operation::reset_oper()
{
	set_oper(undo_t, 0, Line{});
}

void Operation::do_oper()
{
	switch (operation) {
	case undo_t:
		return;
	case insert_t:
		insert_line(doc, lineno, line);
		return;
	case delete_t:
		erase_line(doc, lineno);
		return;
	}
}

void operate(Document& d)
{
	regex insert_pat{ R"(Insert (\w+) as line (\d+))" };
	regex delete_pat{ R"(Delete line (\d+))" };
	regex undo_pat{ R"(Undo last operation)" };
	smatch matches;

	Operation oper{ d };
	print(d, cout);
	cout << '\n';

	for (string command; getline(cin, command); ) 
	try {
		if (regex_search(command, matches, insert_pat)) {
			oper.do_oper();
			oper.set_oper(Operation::insert_t, to<int>(matches[2]), to<Line>(matches[1]));
		}
		else if (regex_search(command, matches, delete_pat)) {
			oper.do_oper();
			oper.set_oper(Operation::delete_t, to<int>(matches[1]));
		}
		else if (regex_search(command, matches, undo_pat)) {
			oper.reset_oper();
		}
		else if (command == "Print") {
			oper.do_oper();
			print(d, cout);
			cout << '\n';
			oper.reset_oper();
		}
		else if (command == "Exit")
			return;
		else
			throw runtime_error("bad command");
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << '\n';
	}
}

int main()
try {
	string iname;
	cout << "Enter the input file name: ";
	cin >> iname;
	ifstream doc{ iname };
	if (!doc)
		throw runtime_error("cannot open file");

	Document my_doc{ doc };
	operate(my_doc);
	print(my_doc, cout);
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	char ch; cin >> ch;
	return 1;
}
catch (...) {
	cerr << "error: unknown error\n";
	char ch; cin >> ch;
	return -1;
}