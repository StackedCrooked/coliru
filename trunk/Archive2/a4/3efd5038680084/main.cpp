#include <iostream>

int main()
{
    int i = 1 ;
    struct A 
    { 
        int i ; 
        int j ; 
        A( int a, int b ) : i(a), j(b) {} 
        A& operator++() { return *this ; };
        A operator++(int) { return *this ; };
        A operator+ (A) { return *this ; }
    };
    
    ///////////  well-defined behaviour //////////////////////
    
    i = i + 1 ; // well defined behaviour (same as below)
    i += 1 ; // well defined behaviour
    
    i = ++i ; // well defined behaviour (same as below)
    i = ( i += 1 ) ; // well defined behaviour (same as below)
    i = ( i = i + 1 ) ; // well defined behaviour

    ++++i ; // well defined behaviour (same as below)
    ( i += 1 ) += 1 ; // well defined behaviour  (same as below)
    ( i = i + 1 ) += 1 ; // well defined behaviour  (same as below)
    i = ( i = i + 1 ) + 1 ; // well defined behaviour
    
    ++++++i ; // well defined behaviour (same as below)
    ( ( i += 1 ) += 1 ) += 1 ; // well defined behaviour
    
    int a[] = { i, ++i, --i } ; // well defined behaviour
    
    A a1 { ++i, ++i } ; // well defined behaviour (compare and contrast with line 51)
    
    A a2 = a1++ + ++a1 ; // no undefined behaviour (indeterminately sequenced != undefined behaviour)
    
    
    
    /////////// undefined behaviour //////////////////////////
    
    i = i++ ; // **** undefined behaviour (unsequenced modifications) ****
    
    i += ++i ; // **** undefined behaviour (unsequenced modification and access) ****
    
    std::cout << i << ++i ; // **** undefined behaviour (unsequenced modification and access) ****
    
    std::cout <<  ++i << ++i ; // **** undefined behaviour (unsequenced modifications) ****
    
    A a3( ++i, ++i ) ; // **** undefined behaviour (unsequenced modifications) ****
    
    void foo( int, int ) ; foo( i, ++i ) ; // **** undefined behaviour (unsequenced modification and access) ****
}
