#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

class String {
public:
	class SubString;

	String();

	String(const char* p);

	String(const String&);
	String& operator=(const String&);

	String(String&& x);
	String& operator=(String&& x);

	~String() { if (short_max < sz) delete[] ptr; }

	char& operator[](int n) { return ptr[n]; }
	char operator[](int n) const { return ptr[n]; }

	char& at(int n) { check(n); return ptr[n]; }
	char at(int n) const { check(n); return ptr[n]; }

	SubString operator()(int begin, int end);

	String& operator+=(char c);

	const char* c_str() { return ptr; }
	const char* c_str() const { return ptr; }

	int size() const { return sz; }
	int capacity() const
	{
		return (sz <= short_max) ? short_max : sz + space;
	}
private:
	static const int short_max = 15;
	int sz;
	char* ptr;
	union {
		int space;
		char ch[short_max + 1];
	};

	void check(int n) const
	{
		if (n < 0 || sz <= n)
			throw std::out_of_range("String::at()");
	}

	void copy_from(const String& x);
	void move_from(String& x);
};

ostream& operator<<(ostream& os, const String& s);
istream& operator>>(istream& is, String& s);

bool operator==(const String& a, const String& b);
bool operator!=(const String& a, const String& b);

char* begin(String& x);
char* end(String& x);
const char* begin(const String& x);
const char* end(const String& x);

String& operator+=(String& a, const String& b);
String operator+(const String& a, const String& b);
String operator"" _s(const char* p, size_t);

class String::SubString {
public:
	void operator=(const String&); // This function cannot return a correct value, 
								   // so it doesn't return a value.
	operator String();
	SubString(String& x, int b, int e)
		:sz{ e - b }, ptr{ &(begin(x))[b] } { }
private:
	int sz;
	char* ptr; // The SubString class doesn't own the resource
};