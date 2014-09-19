#include <iostream>
using namespace std;

void fnc(int const volatile&){cout<<1;}
//void fnc(int*){cout<<2;}

int main() {
    fnc(0);
	// your code goes here
	return 0;
}