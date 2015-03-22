#include <iostream>
 
struct A {
    A(int i) : i(i) {}
    A & operator = ( const A & a )
    { 
    	std::cout << "op=(" << i << "," << a.i << ") ";
    	i = a.i;
    	return *this; 
	}
	int i = 0;
};
 
A & bar( int n ) {
    std::cout << "bar(" << n << ") ";
    return *new A(n);
}
 
int main() {
    bar( 1 ) = bar( 2 ) = bar( 3 );
    std::cout << std::endl;
}