#include <iostream>
#include <string>
#include <cstring>
using namespace std;

char* cat(char s1[], char s2[])
{
	char* p = new char[strlen(s1) + strlen(s2)];
	copy(&s1[0], &s1[strlen(s1) + 1], p);
	copy(&s2[0], &s2[strlen(s2) + 1], p + strlen(s1));
	return p;
}

int main()
{
	char s1[] = "Hello ";
	char s2[] = "World!";
	cout << cat(s1, s2);
}