#include <iostream>
#include <new>
#include <stdexcept>

struct A
{
    A( int i ) { if( i > 100 ) throw std::invalid_argument( "A::A(int) - invalid constructor argument" ) ; }
};

int main()
{
    try
    {
        int* p = new (std::nothrow) int[-1] ;
        delete p ;
    }
    catch( std::exception& error )
    {
        std::cerr << "new failed, exception was thrown. what: " << error.what() << '\n' ;
    }

    try
    {
        A* p = new (std::nothrow) A(500) ;
        delete p ;
    }
    catch( std::exception& error )
    {
        std::cerr << "new failed, exception was thrown. what: " << error.what() << '\n' ;
    }
}
