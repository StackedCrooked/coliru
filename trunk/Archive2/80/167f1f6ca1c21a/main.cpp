#include <utility>
#include <stdio.h>

template<typename T> void _() { puts(__PRETTY_FUNCTION__); }
#define _(statement, x)  statement;  printf(#statement); printf("; // %s is ", #x); _<decltype(x)>();


int main()
{   
    _( int a = 1         , a );
    _( int& b = a        , b );
    _( const int& c = 3  , c );
    _( int&& d = 4       , d );
    _( int&& e = 5       , std::move(e) );
}
