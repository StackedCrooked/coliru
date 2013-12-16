#include <iostream>
#include <string>
using namespace std;

int main() {
    string strGreeting;
	strGreeting = "Hello...";
	string strUser;
	int intAge;
	cout << "Please enter your name";
	cin >> strUser;
	cout << "Please enter your age";
	cin >> intAge;
	cout << strGreeting;
	cout << strUser << endl;
	cout << "You are " << intAge << " years old";
	return 0;
}