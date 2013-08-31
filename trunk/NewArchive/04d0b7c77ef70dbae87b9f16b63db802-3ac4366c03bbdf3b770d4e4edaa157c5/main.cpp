#include <iostream>

template< typename T >
void f() static_assert(std::is_same< T, int >::value)
{ ; }

int main()
{
    
}