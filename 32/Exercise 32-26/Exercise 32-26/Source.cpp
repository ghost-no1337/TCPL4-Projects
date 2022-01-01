#include <iostream>
#include <bitset>
using namespace std;

int main()
{
	cout << bitset<32>(0) << '\n'
		<< bitset<32>(1) << '\n'
		<< bitset<32>(-1) << '\n'
		<< bitset<32>(18) << '\n'
		<< bitset<32>(-18) << '\n'
		<< bitset<32>(INT32_MAX) << '\n';
}