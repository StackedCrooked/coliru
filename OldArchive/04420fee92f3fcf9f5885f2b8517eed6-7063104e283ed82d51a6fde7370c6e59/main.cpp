#include <iostream>
#include <utility>

struct disambiguator_t {};
const auto split = disambiguator_t();

template <typename T>
void Print ( T&& arg ) {
    std::cout << arg << std::endl;
}

void Print (  ) {
    
}

template <typename ...Tn>
void Print ( Tn&&... argn ) {
    
}

template <typename ...Tn, typename ...Tx>
void Cleave ( Tn&&... argn, const disambiguator_t&, Tx&&... argx ) {
    Print( std::forward<Tn>( argn )... );
    
    std::cout << std::endl << "Split!" << std::endl;
    
    Print( std::forward<Tx>( argx )... );
}

int main ( int argc, char** argv ) {
    Cleave( 1, 2, 3, split, 4 5 6 );
    
}