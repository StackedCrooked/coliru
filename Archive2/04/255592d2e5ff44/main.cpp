#include <utility>
#include <iostream>
#include <stdio.h>

template<typename T> void _() { puts(__PRETTY_FUNCTION__); }
#define _(statement, x)  statement;  printf("> " #statement); printf("; // %s is ", #x); _<decltype(x)>();


int main()
{   
    using std::move;
    
    std::cout << "\n=== values, references and rvalue-refs ===\n";
    _( int a = 1            , a );
    _( int& b = a           , b );
    _( const int& c = 3     , c );
    _( int&& d = 4          , d );
    _( int e = 5            , move(e) );
    
        
    std::cout << "\n=== decltype-based type deduction vs auto === \n";
    _( decltype(move(b)) g = std::move(b), g );
    _( auto              f = std::move(a), f );    
    
}
