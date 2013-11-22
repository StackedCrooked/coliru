#include <iostream>
using namespace std;

class C
{
public:    
	C() { cout << "C()" << endl; }
	C( int ) { cout << "implicit C(int)" << endl; }
	C& operator= ( const C& ) { cout << "operator=" << endl; return *this; }
	C( const C& ) { cout << "C(const C&)" << endl; }
};

int main() {
	C c1 = 10;
	return 0;
}