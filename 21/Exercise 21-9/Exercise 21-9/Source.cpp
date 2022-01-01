#include <iostream>
using namespace std;

class Char_vec {
	int sz; 
	char element[1]; 
public: 
	static Char_vec* new_char_vec(int s); 
	char& operator[](int i) { return element[i]; } 
};

Char_vec* Char_vec::new_char_vec(int s)
{
	Char_vec* res = new Char_vec{};
	res->sz = s;
	return res;
}

int main()
{
	int sz = 0;
	cin >> sz;
	Char_vec* cv = Char_vec::new_char_vec(sz);

	for (int i = 0; i < sz; i++) {
		char ch = 0;
		cin >> ch;
		(*cv)[i] = ch;
	}

	for (int i = 0; i < sz; i++)
		cout << (*cv)[i] << '\n';
}