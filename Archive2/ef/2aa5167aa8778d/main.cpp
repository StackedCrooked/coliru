// ************* header.hpp ****************
#include <functional>

template < typename FN, typename... ARGS >
void mylibfun( int a, int b, FN&& fn, ARGS&&... args )
{ if( a<b ) std::bind( std::forward<FN>(fn), std::forward<ARGS>(args)... )() ; }

// ...

// ************* temptest.cpp **************
// #include "header.hpp"
#include <iostream>
#include <string>

int main()
{
    std::string str = "abcdefgh" ;
    mylibfun( 0, 5, &std::string::push_back, std::ref(str), '*' ) ;
    mylibfun( 0, 5, &std::ostream::write,  std::ref(std::cout), str.c_str(), str.size() ) ;
    mylibfun( 0, 5, &std::ostream::put, std::ref(std::cout), '\n' ) ;

    std::string other = "123456" ;
    mylibfun( 0, 5, &std::string::swap, std::ref(str), std::ref(other) ) ;
    std::cout << "str: " << str << "\nother: " << other << '\n' ;
}
