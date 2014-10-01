#include <iostream>
using namespace std;

int main() {
     unsigned int  Value = 0x12345678;
	 char *buffer;
	  char octet;


	  buffer = (char *)&Value;

	  octet = Value & 0xFF;
	  cout << "Octet in pos bit7:0 0x%x\n" << octet<< endl;
	  octet = (Value >> 8) & 0xFF;
	  cout << "Octet in pos bit15:8 0x%x\n" << octet<< endl;
	  octet = (Value >> 16) & 0xFF;
	  cout << "Octet in pos bit23:16 0x%x" << octet << endl;
	  octet = (Value >> 24) & 0xFF;
	  cout << "Octet in pos bit31:24 0x%x" << octet<< endl;


	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}