#include <iostream>
#include <string>
using namespace std;

void encrypt(string& text, string& key)
{
	int i = 0;
	for (char& c : text) {
		c ^= key[i];
		(i < key.size()) ? ++i : i = 0;
	}
}

int main()
{
	cout << "key: ";
	string key;
	getline(cin, key);

	cout << "text: ";
	string text;
	getline(cin, text);

	encrypt(text, key);
	encrypt(text, key);

	for (char& ch : text)
		cout << ch;
}