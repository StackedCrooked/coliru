#include <iostream>
using namespace std;
 
int main() {
    unsigned char uc = -1; // combien vaudra unsigned char
    cout << uc << endl;
	cout << hex << showbase << int(uc) << endl;
	return 0;
}