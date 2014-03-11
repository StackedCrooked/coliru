#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
	string s;
	ifstream createFile(__FILE__);
	
	while (getline(createFile, s)){
		cout << s << endl;
	}
	return 0;
}