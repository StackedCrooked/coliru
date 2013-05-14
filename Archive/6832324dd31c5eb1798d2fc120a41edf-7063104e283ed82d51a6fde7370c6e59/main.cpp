#include <iostream>
#include <utility>

struct disambiguator_t {
    
};

const auto split = disambiguator_t();

template <typename ...Tn>
void Cleave ( Tn&&... argn ) {
    /* How do I collect all Tn up until Tn is the same as disambiguator_t? */
    //std::tuple<Tn... > before_disambiguator;
    
    //std::cout << std::endl << "SMASH!" << std::endl;
    
    //Print<sizeof...(Tx), Tx...>( std::forward<Tx>( argx )... );
}

int main ( int argc, char** argv ) {
    //Cleave( 1, 2, 3, split );
    //Cleave( split, 4, 5, 6 );
    Cleave( 1, 2, 3, disambiguator_t(), 4, 5, 6 );
    
}