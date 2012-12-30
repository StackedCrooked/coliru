#include <iostream>
#include <initializer_list>
#include <array>
#include <iterator>
#include <algorithm>


void InitializerWork ( std::initializer_list<int> arginit ) {
    for ( auto ip = arginit.begin(); ip != arginit.end(); ++ip ) {
        std::cout << *ip << std::endl; 
    }
    std::cout << "So that's an initializer_list..." << std::endl;
}

template<typename TDesired, typename T, std::size_t n>
void GetArg ( const std::array<T, n> table, std::size_t idx, const T& arg ) {
    table[idx++] = &arg;
}

template <typename ...Args>
void VariadicWork ( Args... args ) {
    std::array<const int*, sizeof...(args)> argtable {{
        &args...
    }};
    for ( auto ip : argtable ) {
        std::cout << *ip << std::endl; 
    }
    std::cout << "That's... everything, I think." << std::endl;
}


int main (int argc, char* argv[]) {
    
    InitializerWork( { 20, 40, 80 } );
    VariadicWork( 20, 40, 80 );
    
}