#include <iostream>
#include <array>

int main()
{
    std::array<int,12> value_initialized{} ;
    std::cout << "value_initialized: " ;
    for( int i : value_initialized ) std::cout << i << ' ' ; // 0 0 0 0 0 0 0 0 0 0 0 0
    std::cout << '\n' ;

    std::array<int,12> default_initialized ;
    std::cout << "default_initialized: " ;
    for( int i : default_initialized ) std::cout << i << ' ' ; // undefined behaviour
    std::cout << '\n' ;
}
