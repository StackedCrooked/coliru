#include <iostream>
#include <string>
#include <limits>


using namespace std;

int main(int argc, char ** argv) {

	string s1("abcdef");

	wstring s2(L"aàáäâã");
	wcout << "s2         :" << s2 << endl;
	cout << "sizeof(s2) :" << sizeof(s2) << endl;
	cout << "s2.size() :" << s2.size() << endl;
	cout << "sizeof(char) :" << sizeof(wstring::value_type) << endl;
	cout << "sizeof(wstring::value_type) :" << sizeof(wstring::value_type) << endl;


	return 0;
}