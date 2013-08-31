#include <iostream>
#include <utility>

struct disambiguator_t {};
const auto split = disambiguator_t();

template <std::size_t n>
void Print ( ) {
    
}

template <std::size_t n, typename T, typename ...Tn>
void Print ( T&& arg, Tn&&... argn ) {
    std::cout << arg << std::endl;
    Print<n - 1, Tn...>( std::forward<Tn>( argn )... );
}

/*template <typename ...Tn, typename ...Tx>
void Cleave ( Tn&&... argn, const disambiguator_t&, Tx&&... argx ) {
    Print<Tn...>( std::forward<Tn>( argn )... );
    
    std::cout << std::endl << "SMASH!" << std::endl;
    
    Print<Tx...>( std::forward<Tx>( argx )... );
}*/

template <typename ...Tx>
void Cleave ( const disambiguator_t&, Tx&&... argx ) {
    std::cout << std::endl << "SMASH!" << std::endl;
    
    Print<sizeof...(Tx), Tx...>( std::forward<Tx>( argx )... );
}

int main ( int argc, char** argv ) {
    //Cleave( 1, 2, 3, split );
    Cleave( split, 4, 5, 6 );
    //Cleave( 1, 2, 3, split, 4, 5, 6 );
    
}