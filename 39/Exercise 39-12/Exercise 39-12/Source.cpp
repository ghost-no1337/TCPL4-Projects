#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class File {
public:
	File(const string& f)
		:fname{ f }, fs { new fstream{ fname, ios::in }	} 
	{
		for (char ch = 0; fs->get(ch); )
			buf.push_back(ch);
		fs->close();
		fs->open(fname, ios::out);
	}

	char& operator[](size_t i) { return buf[i]; }

	void save() {
		for (char ch : buf)
			*fs << ch;
	}

	~File() {
		fs->close();
		delete fs;
	}
private:
	string fname;
	fstream* fs;
	vector<char> buf;
};

int main()
{
	string iname;
	cin >> iname;
	File f{ iname };
	int i = 0;
	char ch = 0;
	while (cin >> i >> ch)
		f[i] = ch;
	f.save();
}