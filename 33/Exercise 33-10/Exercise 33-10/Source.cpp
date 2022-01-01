#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	/*string iname, oname;
	cin >> iname >> oname;
	ifstream ifs{ iname };
	if (!ifs)
		throw runtime_error("cannot open required file");
	ofstream ofs{ oname };
	if (!ofs)
		throw runtime_error("cannot open required file");*/

	string buffer;
	for (string s; cin >> s; ) {
		if (s != buffer) {
			buffer = s;
			cout << s << ' ';
		}
	}
}