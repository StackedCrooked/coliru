#include <iostream>
#include <type_traits>

int main()
{
    const char* values[1][2];
    static_assert( std::extent<decltype(values)   >::value == 1, "" );
    static_assert( std::extent<decltype(values), 1>::value == 2, "" );
}