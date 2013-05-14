#include <iostream>
#include <utility>

struct disambiguator_t {};
const auto split = disambiguator_t();

template <std::size_t n, typename T, typename ...Tn>
void Print ( T&& arg, Tn&&... argn ) {
    std::cout << arg << std::endl;
    Print<sizeof...(Tn), Tn...>( std::forward<Tn>( argn )... );
}

template <std::size_t n, typename ...Tn>
void Print (  ) {
    
}

template <typename ...Tn>
void Print ( Tn&&... argn ) {
    Print<sizeof...(Tn), Tn...>( std::forward<Tn>( argn )... );
}

template <typename ...Tn, typename ...Tx>
void Cleave ( Tn&&... argn, const disambiguator_t&, Tx&&... argx ) {
    Print<Tn...>( std::forward<Tn>( argn )... );
    
    std::cout << std::endl << "SMASH!" << std::endl;
    
    Print<Tx...>( std::forward<Tx>( argx )... );
}

int main ( int argc, char** argv ) {
    //Cleave( 1, 2, 3, split );
    Cleave( split, 4, 5, 6 );
    //Cleave( 1, 2, 3, split, 4, 5, 6 );
    
}