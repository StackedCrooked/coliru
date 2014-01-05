#include <type_traits>
#include <iostream>

#include <cstdlib>

struct X {};

struct A
{
    
    template< typename T >
    auto
    f(T && x)
    -> std::enable_if< std::is_same< T, X >::value >::type
    {
        return x;
    }
    
};

int main()
{ 
    return EXIT_SUCCESS;
}

