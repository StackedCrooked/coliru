#include <iostream>
#include <cstddef>

struct A {};
typedef int A::*pd;

int main()
{
    try { throw nullptr ; }
    catch( void* )
    {
        // not caught here
        std::cout << "1. caught exception of type void*\n" ;
    }
    catch( std::nullptr_t )
    {
        // caught here
        std::cout << "1. caught exception of type std::nullptr_t\n" ;
    }

    try { throw pd(nullptr) ; }
    catch( std::nullptr_t )
    {
        // not caught here
        std::cout << "2. caught exception of type std::nullptr_t\n" ;
    }
    catch( pd )
    {
        // caught here
        std::cout << "2. caught exception of type pd\n" ;
    }
}
