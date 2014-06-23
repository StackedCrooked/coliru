#include <iostream>

int foo() 
{ 
    if( std::cin ) // fine; stream is used in a bool context
                   // explicit operator bool() const is called     
        return 100 ; 
    else 
        return -1 ; 
}

bool bar() 
{ return std::cin ; } // *** error: no implicit conversion from std::cin to bool

const void* baz() 
{ return std::cin ; } // *** error: no implicit conversion from std::cin to const void*

