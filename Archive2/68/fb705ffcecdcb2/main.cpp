// ************* header.hpp ****************
#include <functional>

// call function with one extrar (int by value) last parameter
template < typename FN, typename... ARGS >
void mylibfun_add_tail( int a, int b, FN&& fn, ARGS&&... args )
{
    if( a<b )
    {
        const int extra_param = a + b ;
        // call function with an additional int as the last argument
        std::bind( std::forward<FN>(fn), std::forward<ARGS>(args)..., extra_param )() ;
    }
}

// call function with one extrar (int by value) first parameter
template < typename FN, typename... ARGS >
void mylibfun_add_head( int a, int b, FN&& fn, ARGS&&... args )
{
    if( a<b )
    {
        const int extra_param = b - a ;
        // call function with an additional int as the first argument
        std::bind( std::forward<FN>(fn), extra_param, std::forward<ARGS>(args)... )() ;
    }
}

// ************* temptest.cpp **************
// #include "header.hpp"
#include <iostream>
#include <string>

void foo( std::string& str, char ch, int sz )
{
    std::cout << "foo( '" << str << "', '" << ch << "', " << sz << " )\n" ;
    str += std::string( sz, ch ) ;
}

void bar( int sz, std::string& str, char ch )
{
    std::cout << "bar( " << sz << ", '" << str << "', '" << ch << "' )\n" ;
    str = std::string( sz, ch ) + ' ' + str ;
}

int main()
{
    std::string str = "hello world" ;
    std::cout << "str: '" << str << "'\n------------------------\n" ;

    mylibfun_add_tail( 1, 4, foo, std::ref(str), '!' ) ;
    std::cout << "str: '" << str << "'\n------------------------\n" ;

    mylibfun_add_head( 1, 4, bar, std::ref(str), '>' ) ;
    std::cout << "str: '" << str << "'\n------------------------\n" ;
}
