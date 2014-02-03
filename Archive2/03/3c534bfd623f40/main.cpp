#include <iostream>
#include <sstream>

struct A
{
    int i ;
    
    A& operator<< ( int v ) { i += v ; std::cout << i << ' ' ; return *this ; } 
    A& operator<< ( char c ) { ++i ; std::cout << c ; return *this ; } 
    
    A& operator<< ( double d ) & { ++i ; std::cout << d ; return *this ; }
    A&& operator<< ( double d ) && = delete ;
};

struct B { int i ; };

B& operator<< ( B& b, int v ) { b.i += v ; std::cout << b.i << ' ' ; return b ; } 
B&& operator<< ( B&& b, int v ) { b.i += v ; std::cout << b.i << ' ' ; return std::move(b) ; } 

B& operator<< ( B& b, double d ) {++ b.i ; std::cout << d << ' ' ; return b ; } 

int main()
{
    B{23} << 38 ; 
	A{23} << 38 << 57 << 12 << '\n' ; 

    #ifdef ERRORS
    
        A{23} << 34.567 ; // error
        B{23} << 34.567 ; // error
        
    #endif // ERRORS
    
    std::cout << "\n\n----------------------------------\n\n" ;
    
}
