#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "MyString.h"
using namespace std;

int main()
{
	MyString a = "12345678901234567890";
	cout << a << ' ' << a.capacity() << endl;
	a = "Hello";
	cout << a << ' ' << a.capacity() << endl;
	a.insert(0, "str");
	cout << a << ' ' << a.capacity() << endl;
	a += "11";
	a.replace(2, 2, "qw");
	a.erase(0, 2);
	cout << a << ' ' << a.capacity() << endl;
	//MyString s1 = "hello amazing world amazing";
	/*std::string s1 = "abcd";
	std::string s2 = "abce";
	MyString a, b;
	a = "abcd";
	b = "abce";
	std::cout << (a == b) << (a != b) << (a > b) << (a >= b) << (a < b) << (a <= b) << std::endl;
	std::cout << (s1 == s2) << (s1 != s2) << (s1 > s2) << (s1 >= s2) << (s1 < s2) << (s1 <= s2) << std::endl;*/
	return 0;
}