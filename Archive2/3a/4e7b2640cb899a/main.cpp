#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

int main() {
    
	string str= "stroka";
	istringstream is (str);
	is >> setw(6) >> str;
	
	cout << "EOF is:" << boolalpha << is.eof() << endl;
	
	return 0;
}